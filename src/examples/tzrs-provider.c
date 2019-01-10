#include <Elementary.h>
#include <Ecore_Wl2.h>
#include <tizen-remote-surface-client-protocol.h>

#define WIDTH  420
#define HEIGHT 280

static struct tizen_remote_surface_manager *tzrs_mng = NULL;
static struct tizen_remote_surface_provider *tzrs_prov = NULL;

static void
_check_changed_cb(void *data EINA_UNUSED,
                  Evas_Object *obj EINA_UNUSED,
                  void *event_info EINA_UNUSED)
{
   printf("[PROVIDER] Check Winset CB\n");
}

static void
_check_sleep_cb(void *data EINA_UNUSED,
                Evas_Object *obj EINA_UNUSED,
                void *event_info EINA_UNUSED)
{
   printf("[PROVIDER] Sleep 10 seconds\n");

   /* For ping-pong testing */
   sleep(10);
}

static void
_tzrs_prov_cb_res_id(void *data,
                     struct tizen_remote_surface_provider *prov EINA_UNUSED,
                     uint32_t res_id)
{
   Evas_Object *win = (Evas_Object *)data;

   printf("[PROVIDER] Resource ID: %u. Show window\n", res_id);
   evas_object_show(win);
}

static void
_tzrs_prov_cb_vis(void *data EINA_UNUSED,
                  struct tizen_remote_surface_provider *prov EINA_UNUSED,
                  uint32_t vis)
{
   printf("[PROVIDER] Visibility: %u\n", vis);
}

static const struct tizen_remote_surface_provider_listener _tzrs_prov_listener =
{
   _tzrs_prov_cb_res_id,
   _tzrs_prov_cb_vis,
};

static Eina_Bool
_tzrs_init(Evas_Object *win)
{
   Ecore_Wl2_Display *dpy;
   Ecore_Wl2_Window *wl2_win;
   struct wl_surface *surface;
   struct wl_registry *reg;
   Eina_Iterator *itr;
   Ecore_Wl2_Global *global;
   int ver = 5;

   wl2_win = (Ecore_Wl2_Window *)elm_win_wl_window_get(win);
   surface = ecore_wl2_window_surface_get(wl2_win);

   dpy = ecore_wl2_connected_display_get(NULL);
   reg = ecore_wl2_display_registry_get(dpy);
   itr = ecore_wl2_display_globals_get(dpy);

   EINA_ITERATOR_FOREACH(itr, global)
     {
        if (!strcmp(global->interface, "tizen_remote_surface_manager"))
          {
             ver = MIN(global->version, ver);

             tzrs_mng =
                wl_registry_bind(reg,
                                 global->id,
                                 &tizen_remote_surface_manager_interface,
                                 ver);

             printf("TZRS bound version:%d\n", ver);
             break;
          }
     }
   eina_iterator_free(itr);

   /* Now, window can't be visible on the screen directly
    * unless consumer uses this provider.
    */
   tzrs_prov =
     tizen_remote_surface_manager_create_provider(tzrs_mng,
                                                  surface);

   tizen_remote_surface_provider_add_listener(tzrs_prov,
                                              &_tzrs_prov_listener,
                                              win);

   EINA_SAFETY_ON_NULL_RETURN_VAL(tzrs_prov, EINA_FALSE);

   return EINA_TRUE;
}

static void
_tzrs_shutdown(void)
{
   tizen_remote_surface_provider_destroy(tzrs_prov);
   tizen_remote_surface_manager_destroy(tzrs_mng);
}

EAPI_MAIN int
elm_main(int argc EINA_UNUSED,
         char *argv[] EINA_UNUSED)
{
   Evas_Object *win, *bg, *box, *ck;
   Eina_Bool res;

   /* create window with red background color */
   win = elm_win_util_standard_add("TZRS Provider", "TZRS Provider");
   elm_win_autodel_set(win, EINA_TRUE);
   elm_win_alpha_set(win, EINA_FALSE);
   elm_win_aux_hint_add(win, "wm.policy.win.user.geometry", "1");
   bg = elm_bg_add(win);
   evas_object_color_set(bg, 255, 0, 0, 255);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   box = elm_box_add(win);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, box);
   evas_object_show(box);

   ck = elm_check_add(win);
   elm_check_state_set(ck, EINA_FALSE);
   elm_object_text_set(ck, "Test");
   evas_object_size_hint_align_set(ck, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, ck);
   evas_object_show(ck);
   evas_object_smart_callback_add(ck, "changed", _check_changed_cb, NULL);

   ck = elm_check_add(win);
   elm_check_state_set(ck, EINA_FALSE);
   elm_object_text_set(ck, "Sleep");
   evas_object_size_hint_align_set(ck, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, ck);
   evas_object_show(ck);
   evas_object_smart_callback_add(ck, "changed", _check_sleep_cb, NULL);

   /* init */
   res = _tzrs_init(win);
   EINA_SAFETY_ON_FALSE_RETURN_VAL(res, 1);

   evas_object_resize(win, WIDTH, HEIGHT);
   evas_object_show(win);

   /* run mainloop */
   elm_run();

   /* shutdown */
   _tzrs_shutdown();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
