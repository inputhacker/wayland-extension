#include <Elementary.h>
#include <Ecore_Wl2.h>
#include <tizen-remote-surface-client-protocol.h>
#include <wayland-tbm-client.h>
#include <tbm_surface.h>
#include <sys/mman.h>

static struct tizen_remote_surface_manager *tzrs_mng   = NULL;
static struct tizen_remote_surface         *tzrs       = NULL;
static struct wayland_tbm_client           *tbm_client = NULL;
static struct wl_buffer                    *pre_buff   = NULL;
static Evas_Object                         *win        = NULL;
static Evas_Object                         *img_tbm    = NULL;
static Evas_Object                         *img_file   = NULL;

static void _buff_tbm_release(void);
static void _buff_img_file_release(void);

static void
_ev_cb_mouse_down(void *data EINA_UNUSED,
                  Evas *e EINA_UNUSED,
                  Evas_Object *o,
                  void *ev_info)
{
   Evas_Event_Mouse_Down *ev = ev_info;
   int x, y, w, h;

   evas_object_geometry_get(o, &x, &y, &w, &h);

   printf("[CONSUMER] MOUSE DOWN\n"
          "  geomtery (%d,%d) %dx%d\n"
          "  button:%d canvas (%d,%d) output(%d,%d)\n"
          "  radius:%lf rx:%lf ry:%lf pressure:%lf angle:%lf\n"
          "  class:%d subclass:%d name:%s\n"
          "  desc:%s\n",
          x, y, w, h,
          ev->button, ev->canvas.x, ev->canvas.y, ev->output.x, ev->output.y,
          ev->radius, ev->radius_x, ev->radius_y, ev->pressure, ev->angle,
          evas_device_class_get(ev->dev),
          evas_device_subclass_get(ev->dev),
          evas_device_name_get(ev->dev),
          evas_device_description_get(ev->dev));

   tizen_remote_surface_transfer_mouse_event
     (tzrs,
      TIZEN_REMOTE_SURFACE_EVENT_TYPE_MOUSE_DOWN,
      0,
      ev->button,
      ev->canvas.x - x,
      ev->canvas.y - y,
      wl_fixed_from_double(ev->radius_x),
      wl_fixed_from_double(ev->radius_y),
      wl_fixed_from_double(ev->pressure),
      wl_fixed_from_double(ev->angle),
      evas_device_class_get(ev->dev),
      evas_device_subclass_get(ev->dev),
      evas_device_description_get(ev->dev) ?: "noname",
      ev->timestamp);
}

static void
_ev_cb_mouse_up(void *data EINA_UNUSED,
                Evas *e EINA_UNUSED,
                Evas_Object *o,
                void *ev_info)
{
   Evas_Event_Mouse_Up *ev = ev_info;
   int x, y, w, h;

   evas_object_geometry_get(o, &x, &y, &w, &h);

   printf("[CONSUMER] MOUSE UP\n"
          "  geomtery (%d,%d) %dx%d\n"
          "  button:%d canvas (%d,%d) output(%d,%d)\n"
          "  radius:%lf rx:%lf ry:%lf pressure:%lf angle:%lf\n"
          "  class:%d subclass:%d name:%s\n"
          "  desc:%s\n",
          x, y, w, h,
          ev->button, ev->canvas.x, ev->canvas.y, ev->output.x, ev->output.y,
          ev->radius, ev->radius_x, ev->radius_y, ev->pressure, ev->angle,
          evas_device_class_get(ev->dev),
          evas_device_subclass_get(ev->dev),
          evas_device_name_get(ev->dev),
          evas_device_description_get(ev->dev));

   tizen_remote_surface_transfer_mouse_event
     (tzrs,
      TIZEN_REMOTE_SURFACE_EVENT_TYPE_MOUSE_UP,
      0,
      ev->button,
      ev->canvas.x - x,
      ev->canvas.y - y,
      wl_fixed_from_double(ev->radius_x),
      wl_fixed_from_double(ev->radius_y),
      wl_fixed_from_double(ev->pressure),
      wl_fixed_from_double(ev->angle),
      evas_device_class_get(ev->dev),
      evas_device_subclass_get(ev->dev),
      evas_device_description_get(ev->dev) ?: "noname",
      ev->timestamp);
}

static void
_ev_cb_mouse_move(void *data EINA_UNUSED,
                  Evas *e EINA_UNUSED,
                  Evas_Object *o,
                  void *ev_info)
{
   Evas_Event_Mouse_Move *ev = ev_info;
   int x, y, w, h;

   evas_object_geometry_get(o, &x, &y, &w, &h);

   printf("[CONSUMER] MOUSE MOVE\n"
          "  geomtery (%d,%d) %dx%d\n"
          "  cur output(%d,%d) canvas(%d,%d)\n"
          "  radius:%lf rx:%lf ry:%lf pressure:%lf angle:%lf\n"
          "  class:%d subclass:%d name:%s\n"
          "  desc:%s\n",
          x, y, w, h,
          ev->cur.output.x, ev->cur.output.y, ev->cur.canvas.x, ev->cur.canvas.y,
          ev->radius, ev->radius_x, ev->radius_y, ev->pressure, ev->angle,
          evas_device_class_get(ev->dev),
          evas_device_subclass_get(ev->dev),
          evas_device_name_get(ev->dev),
          evas_device_description_get(ev->dev));

   tizen_remote_surface_transfer_mouse_event
     (tzrs,
      TIZEN_REMOTE_SURFACE_EVENT_TYPE_MOUSE_MOVE,
      0,
      0,
      ev->cur.canvas.x - x,
      ev->cur.canvas.y - y,
      wl_fixed_from_double(ev->radius_x),
      wl_fixed_from_double(ev->radius_y),
      wl_fixed_from_double(ev->pressure),
      wl_fixed_from_double(ev->angle),
      evas_device_class_get(ev->dev),
      evas_device_subclass_get(ev->dev),
      evas_device_description_get(ev->dev) ?: "noname",
      ev->timestamp);
}

static void
_ev_cb_mouse_wheel(void *data EINA_UNUSED,
                   Evas *e EINA_UNUSED,
                   Evas_Object *o EINA_UNUSED,
                   void *ev_info)
{
   Evas_Event_Mouse_Wheel *ev = ev_info;

   tizen_remote_surface_transfer_mouse_wheel
     (tzrs,
      ev->direction,
      ev->z,
      evas_device_class_get(ev->dev),
      evas_device_subclass_get(ev->dev),
      evas_device_description_get(ev->dev) ?: "noname",
      ev->timestamp);
}

static Eina_Bool
_ev_cb_key_down(void *data EINA_UNUSED,
                int type,
                void *ev_info)
{
   Ecore_Event_Key *ev = ev_info;

   printf("[CONSUMER] KEY DOWN keycode: %u\n", ev->keycode);

   tizen_remote_surface_transfer_key_event
     (tzrs,
      TIZEN_REMOTE_SURFACE_EVENT_TYPE_KEY_DOWN,
      ev->keycode,
      ecore_device_class_get(ev->dev),
      ecore_device_subclass_get(ev->dev),
      ecore_device_identifier_get(ev->dev),
      ev->timestamp);

   return ECORE_CALLBACK_PASS_ON;
}

static Eina_Bool
_ev_cb_key_up(void *data EINA_UNUSED,
              int type,
              void *ev_info)
{
   Ecore_Event_Key *ev = ev_info;

   printf("[CONSUMER] KEY UP keycode: %u\n", ev->keycode);

   tizen_remote_surface_transfer_key_event
     (tzrs,
      TIZEN_REMOTE_SURFACE_EVENT_TYPE_KEY_UP,
      ev->keycode,
      ecore_device_class_get(ev->dev),
      ecore_device_subclass_get(ev->dev),
      ecore_device_identifier_get(ev->dev),
      ev->timestamp);

   return ECORE_CALLBACK_PASS_ON;
}

/* Deprecated callback */
static void
_tzrs_cb_buffer_update(void *data EINA_UNUSED,
                       struct tizen_remote_surface *tzrs EINA_UNUSED,
                       struct wl_buffer *buffer EINA_UNUSED,
                       uint32_t time EINA_UNUSED)
{
   /* do nothing */
   ;
}

static void
_tzrs_cb_missing(void *data EINA_UNUSED,
                 struct tizen_remote_surface *tzrs)
{
   printf("[CONSUMER] Provider is gone. Remove image object.\n");

   /* delete image object for dead provider */
   _buff_img_file_release();
   _buff_tbm_release();
}

static void
_buff_tbm_update(struct wl_buffer *tbm)
{
   tbm_surface_h tbm_surface;
   Evas_Native_Surface ns;
   int w, h;

   if (!img_tbm)
     {
        Evas *e = evas_object_evas_get(win);
        img_tbm = evas_object_image_filled_add(e);
        evas_object_image_alpha_set(img_tbm, EINA_TRUE);
        evas_object_move(img_tbm, 200, 300);
        evas_object_show(img_tbm);

        /* input transfer will work on only remote surface connected
         * with "tizen_remote_surface_provider" client
         */
        evas_object_event_callback_add(img_tbm, EVAS_CALLBACK_MOUSE_DOWN,  _ev_cb_mouse_down,  NULL);
        evas_object_event_callback_add(img_tbm, EVAS_CALLBACK_MOUSE_UP,    _ev_cb_mouse_up,    NULL);
        evas_object_event_callback_add(img_tbm, EVAS_CALLBACK_MOUSE_MOVE,  _ev_cb_mouse_move,  NULL);
        evas_object_event_callback_add(img_tbm, EVAS_CALLBACK_MOUSE_WHEEL, _ev_cb_mouse_wheel, NULL);
        ecore_event_handler_add(ECORE_EVENT_KEY_DOWN,                      _ev_cb_key_down,    NULL);
        ecore_event_handler_add(ECORE_EVENT_KEY_UP,                        _ev_cb_key_up,      NULL);

        tizen_remote_surface_transfer_visibility
          (tzrs, TIZEN_REMOTE_SURFACE_VISIBILITY_TYPE_VISIBLE);
     }

   /* get tbm surface from buffer */
   tbm_surface = wl_buffer_get_user_data(tbm);
   w = tbm_surface_get_width(tbm_surface);
   h = tbm_surface_get_height(tbm_surface);

   /* set native surface */
   memset(&ns, 0, sizeof(Evas_Native_Surface));
   ns.version = EVAS_NATIVE_SURFACE_VERSION;
   ns.type = EVAS_NATIVE_SURFACE_TBM;
   ns.data.tbm.buffer = tbm_surface;
   evas_object_resize(img_tbm, w, h);
   evas_object_image_size_set(img_tbm, w, h);
   evas_object_image_native_surface_set(img_tbm, &ns);

   /* set dirty for updating image object */
   evas_object_image_pixels_dirty_set(img_tbm, EINA_TRUE);
}

static void
_buff_tbm_release(void)
{
   if (!img_tbm) return;

   /* set null to previous object for the tbm type */
   evas_object_image_native_surface_set(img_tbm, NULL);
   evas_object_del(img_tbm);
   img_tbm = NULL;
}

static void
_buff_img_file_update(int32_t fd,
                      uint32_t size)
{
   char *map;

   map = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
   EINA_SAFETY_ON_NULL_RETURN(map);

   if (!img_file)
     {
        Evas *e = evas_object_evas_get(win);
        img_file = evas_object_image_filled_add(e);
        evas_object_image_alpha_set(img_file, EINA_TRUE);
        evas_object_move(img_file, 200, 300);
        evas_object_show(img_file);
     }

   evas_object_image_memfile_set(img_file, map, size, NULL, NULL);
   evas_object_resize(img_file, 500, 500);

   munmap(map, size);
}

static void
_buff_img_file_release(void)
{
   if (!img_file) return;

   /* delete previous object for the image file type */
   evas_object_del(img_file);
   img_file = NULL;
}

static void
_tzrs_cb_changed_buffer(void *data EINA_UNUSED,
                        struct tizen_remote_surface *tzrs EINA_UNUSED,
                        uint32_t type,
                        struct wl_buffer *tbm,
                        int32_t fd,
                        uint32_t size,
                        uint32_t time EINA_UNUSED,
                        struct wl_array *keys EINA_UNUSED)
{
   switch (type)
     {
      case TIZEN_REMOTE_SURFACE_BUFFER_TYPE_TBM:
         _buff_tbm_update(tbm);
         _buff_img_file_release();
         break;
      case TIZEN_REMOTE_SURFACE_BUFFER_TYPE_IMAGE_FILE:
         _buff_img_file_update(fd, size);
         _buff_tbm_release();
         break;
      default:
         break;
     }

   if (pre_buff)
     tizen_remote_surface_release(tzrs, pre_buff);

   pre_buff = tbm;

   /* close passed fd */
   printf("FD: %d\n", fd);
   close(fd);
}

static void
_tzrs_cb_input_ev_filter(void *data EINA_UNUSED,
                         struct tizen_remote_surface *tzrs EINA_UNUSED,
                         uint32_t ev_filter EINA_UNUSED)
{
   /* do nothing */
   ;
}

static const struct tizen_remote_surface_listener _tzrs_listener =
{
   _tzrs_cb_buffer_update, /* deprecated. use changed_buffer instead of it. */
   _tzrs_cb_missing,
   _tzrs_cb_changed_buffer,
   _tzrs_cb_input_ev_filter,
};

static Eina_Bool
_tzrs_init(uint32_t res_id,
           Eina_Bool use_tzrs_bind)
{
   Ecore_Wl2_Display *dpy;
   Ecore_Wl2_Window *wl2_win;
   struct wl_surface *surface;
   struct wl_registry *reg;
   struct wl_display *wl_dpy;
   Eina_Iterator *itr;
   Ecore_Wl2_Global *global;
   int ver = 6;
   struct wl_tbm *wl_tbm;

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

             printf("[CONSUMER] TZRS bound version:%d\n", ver);
             break;
          }
     }
   eina_iterator_free(itr);

   EINA_SAFETY_ON_NULL_RETURN_VAL(tzrs_mng, EINA_FALSE);

   /* get wayland tbm */
   wl_dpy = ecore_wl2_display_get(dpy);
   tbm_client = wayland_tbm_client_init(wl_dpy);
   wl_tbm = wayland_tbm_client_get_wl_tbm(tbm_client);

   /* Create tizen remote surface for showing buffer of provider winodw
    *
    * Since TIZEN_REMOTE_SURFACE_MANAGER_CREATE_SURFACE_WITH_WL_SURFACE_SINCE_VERSION,
    * client can request create tizen remote surface with its wl_surfacea(will
    * contain tizen remote surface) to tizen remote surface manager.
    */
   if (ver >= TIZEN_REMOTE_SURFACE_MANAGER_CREATE_SURFACE_WITH_WL_SURFACE_SINCE_VERSION)
     tzrs =
        tizen_remote_surface_manager_create_surface_with_wl_surface(tzrs_mng,
                                                                    res_id,
                                                                    wl_tbm,
                                                                    surface);
   else
     tzrs =
        tizen_remote_surface_manager_create_surface(tzrs_mng, res_id, wl_tbm);

   tizen_remote_surface_add_listener(tzrs, &_tzrs_listener, NULL);

   /* Inform server what wl_surface is container oftizen remote surface.
    *
    * Since TIZEN_REMOTE_SURFACE_MANAGER_CREATE_SURFACE_WITH_WL_SURFACE_SINCE_VERSION,
    * client can inform it through new request(tizen_remote_surface_manager_create_surface_with_wl_surface)
    */
   if (ver < TIZEN_REMOTE_SURFACE_MANAGER_CREATE_SURFACE_WITH_WL_SURFACE_SINCE_VERSION)
     tizen_remote_surface_set_owner(tzrs, surface);

   /* start redirection of provider's buffer update */
   tizen_remote_surface_redirect(tzrs);

   EINA_SAFETY_ON_NULL_RETURN_VAL(tzrs, EINA_FALSE);

   /* <bind_surface>
    * it means your bound surface will be updated automatically with
    * provider's buffer updating by display server. and you can't receive 
    * buffer_update event of tizen_remote_surface.
    */
   if (use_tzrs_bind)
     {
        wl2_win = ecore_wl2_window_new(dpy, NULL, 0, 0, 720, 1280);
        surface = ecore_wl2_window_surface_get(wl2_win);

        tizen_remote_surface_manager_bind_surface(tzrs_mng, surface, tzrs);

        ecore_wl2_window_raise(wl2_win);
        ecore_wl2_window_position_set(wl2_win, 0, 0);
        ecore_wl2_window_show(wl2_win);

        tizen_remote_surface_transfer_visibility
          (tzrs, TIZEN_REMOTE_SURFACE_VISIBILITY_TYPE_VISIBLE);
     }

   return EINA_TRUE;
}

static void
_tzrs_shutdown(void)
{
   tizen_remote_surface_destroy(tzrs);
   tizen_remote_surface_manager_destroy(tzrs_mng);
   wayland_tbm_client_deinit(tbm_client);
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   Evas_Object *bg, *box, *ck;
   int rots[] = { 0, 90, 180, 270 };
   Eina_Bool res;
   uint32_t res_id = 0;
   Eina_Bool use_tzrs_bind = EINA_FALSE;

   EINA_SAFETY_ON_FALSE_RETURN_VAL(argc == 2, 1);

   res_id = atoi(argv[1]);
   printf("[CONSUMER] Given Resource ID: %u\n", res_id);

   /* create window with blue background color and rotatable */
   win = elm_win_util_standard_add("TZRS Consumer", "TZRS Consumer");
   elm_win_wm_rotation_available_rotations_set(win, rots, 4);
   elm_win_autodel_set(win, EINA_TRUE);
   elm_win_alpha_set(win, EINA_FALSE);
   bg = elm_bg_add(win);
   evas_object_color_set(bg, 50, 50, 220, 255);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   box = elm_box_add(win);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, box);
   evas_object_show(box);

   ck = elm_check_add(win);
   elm_check_state_set(ck, EINA_FALSE);
   elm_object_text_set(ck, "Test CK");
   evas_object_size_hint_align_set(ck, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, ck);
   evas_object_show(ck);

   /* init */
   res = _tzrs_init(res_id, use_tzrs_bind);
   EINA_SAFETY_ON_FALSE_RETURN_VAL(res, 1);

   evas_object_show(win);

   /* run mainloop */
   elm_run();

   /* shutdown */
   _tzrs_shutdown();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
