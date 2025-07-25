##########################################################################################################################
# File automatically-generated by STM32forVSCode
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#   2024-04-27 - Added env file inclusion. 
#                Added way to overide: build directory, target name and optimisation.
#                Added GCC_PATH by env file to not make the makefile machine dependent.
#                Currently folder structure in build directory is preserved
#                Switching of debug/release build output folder now happens based on debug flag
#   2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# Environment Variables
######################################
# Imports the environment file in which the compiler and other tooling is set
# for the build machine.
# This can also be used to overwrite some makefile variables
file_exists = $(or $(and $(wildcard $(1)),1),0)
ifeq ($(call file_exists,.stm32env),1)
  include .stm32env
endif

######################################
# Target
######################################
# This is the name of the embedded target which will be build
# The final file name will also have debug or release appended to it.
TARGET ?= indoor-bike-computer

#######################################
# Build directories
#######################################
# Build path can be overwritten when calling make or setting the environment variable
# in .stm32env

BUILD_DIRECTORY ?= build


######################################
# Optimization
######################################
# Optimization is switched based upon the DEBUG variable. If set to 1
# it will be build in debug mode with the Og optimization flag (optimized for debugging).
# If set to 0 (false) then by default the variable is used in the configuration yaml
# This can also be overwritten using the environment variable or by overwriting it
# by calling make with the OPTIMIZATION variable e.g.:
# make -f STM32Make.make -j 16  OPTIMIZATION=Os

# variable which determines if it is a debug build
DEBUG ?= 1

# debug flags when debug is defined
OPTIMIZATION ?= -Og

RELEASE_DIRECTORY = $(BUILD_DIRECTORY)/debug
ifeq ($(DEBUG),1)
  # Sets debugging optimization -Og and the debug information output
  OPTIMIZATION_FLAGS += -Og -g -gdwarf -ggdb
  $(TARGET) := $(TARGET)-debug
  RELEASE_DIRECTORY := $(BUILD_DIRECTORY)/debug
else
  OPTIMIZATION_FLAGS += $(OPTIMIZATION)
  $(TARGET) := $(TARGET)-release
  RELEASE_DIRECTORY := $(BUILD_DIRECTORY)/release
endif

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Lib/LVGL/src/core/lv_group.c \
Core/Lib/LVGL/src/core/lv_obj.c \
Core/Lib/LVGL/src/core/lv_obj_class.c \
Core/Lib/LVGL/src/core/lv_obj_draw.c \
Core/Lib/LVGL/src/core/lv_obj_event.c \
Core/Lib/LVGL/src/core/lv_obj_id_builtin.c \
Core/Lib/LVGL/src/core/lv_obj_pos.c \
Core/Lib/LVGL/src/core/lv_obj_property.c \
Core/Lib/LVGL/src/core/lv_obj_scroll.c \
Core/Lib/LVGL/src/core/lv_obj_style.c \
Core/Lib/LVGL/src/core/lv_obj_style_gen.c \
Core/Lib/LVGL/src/core/lv_obj_tree.c \
Core/Lib/LVGL/src/core/lv_refr.c \
Core/Lib/LVGL/src/display/lv_display.c \
Core/Lib/LVGL/src/draw/lv_draw.c \
Core/Lib/LVGL/src/draw/lv_draw_arc.c \
Core/Lib/LVGL/src/draw/lv_draw_buf.c \
Core/Lib/LVGL/src/draw/lv_draw_image.c \
Core/Lib/LVGL/src/draw/lv_draw_label.c \
Core/Lib/LVGL/src/draw/lv_draw_line.c \
Core/Lib/LVGL/src/draw/lv_draw_mask.c \
Core/Lib/LVGL/src/draw/lv_draw_rect.c \
Core/Lib/LVGL/src/draw/lv_draw_triangle.c \
Core/Lib/LVGL/src/draw/lv_draw_vector.c \
Core/Lib/LVGL/src/draw/lv_image_decoder.c \
Core/Lib/LVGL/src/draw/nxp/pxp/lv_draw_buf_pxp.c \
Core/Lib/LVGL/src/draw/nxp/pxp/lv_draw_pxp.c \
Core/Lib/LVGL/src/draw/nxp/pxp/lv_draw_pxp_fill.c \
Core/Lib/LVGL/src/draw/nxp/pxp/lv_draw_pxp_img.c \
Core/Lib/LVGL/src/draw/nxp/pxp/lv_draw_pxp_layer.c \
Core/Lib/LVGL/src/draw/nxp/pxp/lv_pxp_cfg.c \
Core/Lib/LVGL/src/draw/nxp/pxp/lv_pxp_osa.c \
Core/Lib/LVGL/src/draw/nxp/pxp/lv_pxp_utils.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_buf_vglite.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_vglite.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_vglite_arc.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_vglite_border.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_vglite_fill.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_vglite_img.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_vglite_label.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_vglite_layer.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_vglite_line.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_draw_vglite_triangle.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_vglite_buf.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_vglite_matrix.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_vglite_path.c \
Core/Lib/LVGL/src/draw/nxp/vglite/lv_vglite_utils.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d_arc.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d_border.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d_fill.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d_image.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d_label.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d_line.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d_mask_rectangle.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d_triangle.c \
Core/Lib/LVGL/src/draw/renesas/dave2d/lv_draw_dave2d_utils.c \
Core/Lib/LVGL/src/draw/sdl/lv_draw_sdl.c \
Core/Lib/LVGL/src/draw/sw/blend/lv_draw_sw_blend.c \
Core/Lib/LVGL/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888.c \
Core/Lib/LVGL/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565.c \
Core/Lib/LVGL/src/draw/sw/blend/lv_draw_sw_blend_to_rgb888.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_arc.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_border.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_box_shadow.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_fill.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_gradient.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_img.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_letter.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_line.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_mask.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_mask_rect.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_transform.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_triangle.c \
Core/Lib/LVGL/src/draw/sw/lv_draw_sw_vector.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_buf_vg_lite.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_arc.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_border.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_box_shadow.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_fill.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_img.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_label.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_layer.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_line.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_mask_rect.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_triangle.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_draw_vg_lite_vector.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_vg_lite_decoder.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_vg_lite_grad.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_vg_lite_math.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_vg_lite_path.c \
Core/Lib/LVGL/src/draw/vg_lite/lv_vg_lite_utils.c \
Core/Lib/LVGL/src/drivers/display/drm/lv_linux_drm.c \
Core/Lib/LVGL/src/drivers/display/fb/lv_linux_fbdev.c \
Core/Lib/LVGL/src/drivers/display/ili9341/lv_ili9341.c \
Core/Lib/LVGL/src/drivers/display/lcd/lv_lcd_generic_mipi.c \
Core/Lib/LVGL/src/drivers/display/st7735/lv_st7735.c \
Core/Lib/LVGL/src/drivers/display/st7789/lv_st7789.c \
Core/Lib/LVGL/src/drivers/display/st7796/lv_st7796.c \
Core/Lib/LVGL/src/drivers/evdev/lv_evdev.c \
Core/Lib/LVGL/src/drivers/libinput/lv_libinput.c \
Core/Lib/LVGL/src/drivers/libinput/lv_xkb.c \
Core/Lib/LVGL/src/drivers/nuttx/lv_nuttx_cache.c \
Core/Lib/LVGL/src/drivers/nuttx/lv_nuttx_entry.c \
Core/Lib/LVGL/src/drivers/nuttx/lv_nuttx_fbdev.c \
Core/Lib/LVGL/src/drivers/nuttx/lv_nuttx_image_cache.c \
Core/Lib/LVGL/src/drivers/nuttx/lv_nuttx_lcd.c \
Core/Lib/LVGL/src/drivers/nuttx/lv_nuttx_libuv.c \
Core/Lib/LVGL/src/drivers/nuttx/lv_nuttx_profiler.c \
Core/Lib/LVGL/src/drivers/nuttx/lv_nuttx_touchscreen.c \
Core/Lib/LVGL/src/drivers/sdl/lv_sdl_keyboard.c \
Core/Lib/LVGL/src/drivers/sdl/lv_sdl_mouse.c \
Core/Lib/LVGL/src/drivers/sdl/lv_sdl_mousewheel.c \
Core/Lib/LVGL/src/drivers/sdl/lv_sdl_window.c \
Core/Lib/LVGL/src/drivers/windows/lv_windows_context.c \
Core/Lib/LVGL/src/drivers/windows/lv_windows_display.c \
Core/Lib/LVGL/src/drivers/windows/lv_windows_input.c \
Core/Lib/LVGL/src/drivers/x11/lv_x11_display.c \
Core/Lib/LVGL/src/drivers/x11/lv_x11_input.c \
Core/Lib/LVGL/src/font/lv_binfont_loader.c \
Core/Lib/LVGL/src/font/lv_font.c \
Core/Lib/LVGL/src/font/lv_font_dejavu_16_persian_hebrew.c \
Core/Lib/LVGL/src/font/lv_font_fmt_txt.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_10.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_12.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_14.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_16.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_18.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_20.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_22.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_24.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_26.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_28.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_28_compressed.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_30.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_32.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_34.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_36.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_38.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_40.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_42.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_44.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_46.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_48.c \
Core/Lib/LVGL/src/font/lv_font_montserrat_8.c \
Core/Lib/LVGL/src/font/lv_font_simsun_16_cjk.c \
Core/Lib/LVGL/src/font/lv_font_unscii_16.c \
Core/Lib/LVGL/src/font/lv_font_unscii_8.c \
Core/Lib/LVGL/src/indev/lv_indev.c \
Core/Lib/LVGL/src/indev/lv_indev_scroll.c \
Core/Lib/LVGL/src/layouts/flex/lv_flex.c \
Core/Lib/LVGL/src/layouts/grid/lv_grid.c \
Core/Lib/LVGL/src/layouts/lv_layout.c \
Core/Lib/LVGL/src/libs/barcode/code128.c \
Core/Lib/LVGL/src/libs/barcode/lv_barcode.c \
Core/Lib/LVGL/src/libs/bin_decoder/lv_bin_decoder.c \
Core/Lib/LVGL/src/libs/bmp/lv_bmp.c \
Core/Lib/LVGL/src/libs/ffmpeg/lv_ffmpeg.c \
Core/Lib/LVGL/src/libs/freetype/lv_freetype.c \
Core/Lib/LVGL/src/libs/freetype/lv_freetype_glyph.c \
Core/Lib/LVGL/src/libs/freetype/lv_freetype_image.c \
Core/Lib/LVGL/src/libs/freetype/lv_freetype_outline.c \
Core/Lib/LVGL/src/libs/freetype/lv_ftsystem.c \
Core/Lib/LVGL/src/libs/fsdrv/lv_fs_cbfs.c \
Core/Lib/LVGL/src/libs/fsdrv/lv_fs_fatfs.c \
Core/Lib/LVGL/src/libs/fsdrv/lv_fs_littlefs.c \
Core/Lib/LVGL/src/libs/fsdrv/lv_fs_memfs.c \
Core/Lib/LVGL/src/libs/fsdrv/lv_fs_posix.c \
Core/Lib/LVGL/src/libs/fsdrv/lv_fs_stdio.c \
Core/Lib/LVGL/src/libs/fsdrv/lv_fs_win32.c \
Core/Lib/LVGL/src/libs/gif/gifdec.c \
Core/Lib/LVGL/src/libs/gif/lv_gif.c \
Core/Lib/LVGL/src/libs/libjpeg_turbo/lv_libjpeg_turbo.c \
Core/Lib/LVGL/src/libs/libpng/lv_libpng.c \
Core/Lib/LVGL/src/libs/lodepng/lodepng.c \
Core/Lib/LVGL/src/libs/lodepng/lv_lodepng.c \
Core/Lib/LVGL/src/libs/lz4/lz4.c \
Core/Lib/LVGL/src/libs/qrcode/lv_qrcode.c \
Core/Lib/LVGL/src/libs/qrcode/qrcodegen.c \
Core/Lib/LVGL/src/libs/rle/lv_rle.c \
Core/Lib/LVGL/src/libs/rlottie/lv_rlottie.c \
Core/Lib/LVGL/src/libs/tiny_ttf/lv_tiny_ttf.c \
Core/Lib/LVGL/src/libs/tjpgd/lv_tjpgd.c \
Core/Lib/LVGL/src/libs/tjpgd/tjpgd.c \
Core/Lib/LVGL/src/lv_init.c \
Core/Lib/LVGL/src/misc/cache/_lv_cache_lru_rb.c \
Core/Lib/LVGL/src/misc/cache/lv_cache.c \
Core/Lib/LVGL/src/misc/cache/lv_cache_entry.c \
Core/Lib/LVGL/src/misc/cache/lv_image_cache.c \
Core/Lib/LVGL/src/misc/lv_anim.c \
Core/Lib/LVGL/src/misc/lv_anim_timeline.c \
Core/Lib/LVGL/src/misc/lv_area.c \
Core/Lib/LVGL/src/misc/lv_array.c \
Core/Lib/LVGL/src/misc/lv_async.c \
Core/Lib/LVGL/src/misc/lv_bidi.c \
Core/Lib/LVGL/src/misc/lv_color.c \
Core/Lib/LVGL/src/misc/lv_color_op.c \
Core/Lib/LVGL/src/misc/lv_event.c \
Core/Lib/LVGL/src/misc/lv_fs.c \
Core/Lib/LVGL/src/misc/lv_ll.c \
Core/Lib/LVGL/src/misc/lv_log.c \
Core/Lib/LVGL/src/misc/lv_lru.c \
Core/Lib/LVGL/src/misc/lv_math.c \
Core/Lib/LVGL/src/misc/lv_palette.c \
Core/Lib/LVGL/src/misc/lv_profiler_builtin.c \
Core/Lib/LVGL/src/misc/lv_rb.c \
Core/Lib/LVGL/src/misc/lv_style.c \
Core/Lib/LVGL/src/misc/lv_style_gen.c \
Core/Lib/LVGL/src/misc/lv_templ.c \
Core/Lib/LVGL/src/misc/lv_text.c \
Core/Lib/LVGL/src/misc/lv_text_ap.c \
Core/Lib/LVGL/src/misc/lv_timer.c \
Core/Lib/LVGL/src/misc/lv_utils.c \
Core/Lib/LVGL/src/osal/lv_cmsis_rtos2.c \
Core/Lib/LVGL/src/osal/lv_freertos.c \
Core/Lib/LVGL/src/osal/lv_os_none.c \
Core/Lib/LVGL/src/osal/lv_pthread.c \
Core/Lib/LVGL/src/osal/lv_rtthread.c \
Core/Lib/LVGL/src/osal/lv_windows.c \
Core/Lib/LVGL/src/others/file_explorer/lv_file_explorer.c \
Core/Lib/LVGL/src/others/fragment/lv_fragment.c \
Core/Lib/LVGL/src/others/fragment/lv_fragment_manager.c \
Core/Lib/LVGL/src/others/gridnav/lv_gridnav.c \
Core/Lib/LVGL/src/others/ime/lv_ime_pinyin.c \
Core/Lib/LVGL/src/others/imgfont/lv_imgfont.c \
Core/Lib/LVGL/src/others/monkey/lv_monkey.c \
Core/Lib/LVGL/src/others/observer/lv_observer.c \
Core/Lib/LVGL/src/others/snapshot/lv_snapshot.c \
Core/Lib/LVGL/src/others/sysmon/lv_sysmon.c \
Core/Lib/LVGL/src/others/vg_lite_tvg/vg_lite_matrix.c \
Core/Lib/LVGL/src/stdlib/builtin/lv_mem_core_builtin.c \
Core/Lib/LVGL/src/stdlib/builtin/lv_sprintf_builtin.c \
Core/Lib/LVGL/src/stdlib/builtin/lv_string_builtin.c \
Core/Lib/LVGL/src/stdlib/builtin/lv_tlsf.c \
Core/Lib/LVGL/src/stdlib/clib/lv_mem_core_clib.c \
Core/Lib/LVGL/src/stdlib/clib/lv_sprintf_clib.c \
Core/Lib/LVGL/src/stdlib/clib/lv_string_clib.c \
Core/Lib/LVGL/src/stdlib/lv_mem.c \
Core/Lib/LVGL/src/stdlib/micropython/lv_mem_core_micropython.c \
Core/Lib/LVGL/src/stdlib/rtthread/lv_mem_core_rtthread.c \
Core/Lib/LVGL/src/stdlib/rtthread/lv_sprintf_rtthread.c \
Core/Lib/LVGL/src/stdlib/rtthread/lv_string_rtthread.c \
Core/Lib/LVGL/src/themes/default/lv_theme_default.c \
Core/Lib/LVGL/src/themes/lv_theme.c \
Core/Lib/LVGL/src/themes/mono/lv_theme_mono.c \
Core/Lib/LVGL/src/themes/simple/lv_theme_simple.c \
Core/Lib/LVGL/src/tick/lv_tick.c \
Core/Lib/LVGL/src/widgets/animimage/lv_animimage.c \
Core/Lib/LVGL/src/widgets/arc/lv_arc.c \
Core/Lib/LVGL/src/widgets/bar/lv_bar.c \
Core/Lib/LVGL/src/widgets/button/lv_button.c \
Core/Lib/LVGL/src/widgets/buttonmatrix/lv_buttonmatrix.c \
Core/Lib/LVGL/src/widgets/calendar/lv_calendar.c \
Core/Lib/LVGL/src/widgets/calendar/lv_calendar_header_arrow.c \
Core/Lib/LVGL/src/widgets/calendar/lv_calendar_header_dropdown.c \
Core/Lib/LVGL/src/widgets/canvas/lv_canvas.c \
Core/Lib/LVGL/src/widgets/chart/lv_chart.c \
Core/Lib/LVGL/src/widgets/checkbox/lv_checkbox.c \
Core/Lib/LVGL/src/widgets/dropdown/lv_dropdown.c \
Core/Lib/LVGL/src/widgets/image/lv_image.c \
Core/Lib/LVGL/src/widgets/imagebutton/lv_imagebutton.c \
Core/Lib/LVGL/src/widgets/keyboard/lv_keyboard.c \
Core/Lib/LVGL/src/widgets/label/lv_label.c \
Core/Lib/LVGL/src/widgets/led/lv_led.c \
Core/Lib/LVGL/src/widgets/line/lv_line.c \
Core/Lib/LVGL/src/widgets/list/lv_list.c \
Core/Lib/LVGL/src/widgets/menu/lv_menu.c \
Core/Lib/LVGL/src/widgets/msgbox/lv_msgbox.c \
Core/Lib/LVGL/src/widgets/objx_templ/lv_objx_templ.c \
Core/Lib/LVGL/src/widgets/roller/lv_roller.c \
Core/Lib/LVGL/src/widgets/scale/lv_scale.c \
Core/Lib/LVGL/src/widgets/slider/lv_slider.c \
Core/Lib/LVGL/src/widgets/span/lv_span.c \
Core/Lib/LVGL/src/widgets/spinbox/lv_spinbox.c \
Core/Lib/LVGL/src/widgets/spinner/lv_spinner.c \
Core/Lib/LVGL/src/widgets/switch/lv_switch.c \
Core/Lib/LVGL/src/widgets/table/lv_table.c \
Core/Lib/LVGL/src/widgets/tabview/lv_tabview.c \
Core/Lib/LVGL/src/widgets/textarea/lv_textarea.c \
Core/Lib/LVGL/src/widgets/tileview/lv_tileview.c \
Core/Lib/LVGL/src/widgets/win/lv_win.c \
Core/Src/Components/GUI/Elements/common/alert_modal.c \
Core/Src/Components/GUI/Elements/common/loading_label.c \
Core/Src/Components/GUI/Elements/common/page_header.c \
Core/Src/Components/GUI/Elements/history/run_list.c \
Core/Src/Components/GUI/Elements/history/run_list_item.c \
Core/Src/Components/GUI/Elements/history/run_modal.c \
Core/Src/Components/GUI/Elements/history/run_statistics.c \
Core/Src/Components/GUI/Elements/live/live_controls.c \
Core/Src/Components/GUI/Elements/live/measurement_box.c \
Core/Src/Components/GUI/Elements/live/measurement_chart.c \
Core/Src/Components/GUI/Elements/live/timer_box.c \
Core/Src/Components/GUI/Screens/main_screen.c \
Core/Src/Components/GUI/Tabs/main_tabview.c \
Core/Src/Components/GUI/Tabs/main_tabview_history.c \
Core/Src/Components/GUI/Tabs/main_tabview_live.c \
Core/Src/Components/GUI/Tabs/main_tabview_settings.c \
Core/Src/Components/GUI/gui.c \
Core/Src/Components/bike.c \
Core/Src/Drivers/er_tft035.c \
Core/Src/Drivers/max17055.c \
Core/Src/Drivers/mcp3421.c \
Core/Src/Drivers/sd_card.c \
Core/Src/Drivers/stoptimer.c \
Core/Src/ESP32/esp32_uart.c \
Core/Src/Handlers/config.c \
Core/Src/Handlers/data.c \
Core/Src/Handlers/input.c \
Core/Src/Handlers/state.c \
Core/Src/Utils/binary.c \
Core/Src/Utils/buffer.c \
Core/Src/main.c \
Core/Src/stm32f4xx_hal_msp.c \
Core/Src/stm32f4xx_it.c \
Core/Src/system_stm32f4xx.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c \
FATFS/App/fatfs.c \
FATFS/Target/bsp_driver_sd.c \
FATFS/Target/fatfs_platform.c \
FATFS/Target/sd_diskio.c \
Middlewares/Third_Party/FatFs/src/diskio.c \
Middlewares/Third_Party/FatFs/src/ff.c \
Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
Middlewares/Third_Party/FatFs/src/option/ccsbcs.c \
Middlewares/Third_Party/FatFs/src/option/syscall.c


CPP_SOURCES = \
Core/Lib/LVGL/src/drivers/display/tft_espi/lv_tft_espi.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgAnimation.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgBezier.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgCanvas.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgCapi.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgCompressor.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgFill.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgInitializer.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgLoader.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgMath.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgPaint.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgPicture.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgRawLoader.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgRender.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSaver.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgScene.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgShape.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgStr.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSvgCssStyle.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSvgLoader.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSvgPath.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSvgSceneBuilder.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSvgUtil.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwCanvas.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwFill.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwImage.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwMath.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwMemPool.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwRaster.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwRenderer.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwRle.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwShape.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgSwStroke.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgTaskScheduler.cpp \
Core/Lib/LVGL/src/libs/thorvg/tvgXmlParser.cpp \
Core/Lib/LVGL/src/others/vg_lite_tvg/vg_lite_tvg.cpp


# ASM sources
ASM_SOURCES =  \
startup_stm32f446xx.s


#######################################
# Tools
#######################################
ARM_PREFIX = arm-none-eabi-
POSTFIX = "
PREFIX = "
# The gcc compiler bin path can be defined in the make command via ARM_GCC_PATH variable (e.g.: make ARM_GCC_PATH=xxx)
# or it can be added to the PATH environment variable.
# By default the variable be used from the environment file: .stm32env.
# if it is not defined

ifdef ARM_GCC_PATH
    CC = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)gcc$(POSTFIX)
    CXX = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)g++$(POSTFIX)
    AS = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)gcc$(POSTFIX) -x assembler-with-cpp
    CP = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)objcopy$(POSTFIX)
    SZ = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)size$(POSTFIX)
    DP = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)objdump$(POSTFIX)
else
  CC ?= $(ARM_PREFIX)gcc
  CXX ?= $(ARM_PREFIX)g++$
  AS ?= $(ARM_PREFIX)gcc -x assembler-with-cpp
  CP ?= $(ARM_PREFIX)objcopy
  SZ ?= $(ARM_PREFIX)size
  DP ?= $(ARM_PREFIX)objdump
endif

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
LSS = $(DP) -h -S

# Flash and debug tools
# Default is openocd however will be gotten from the env file when existing
OPENOCD ?= openocd


#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DSTM32F446xx \
-DUSE_HAL_DRIVER


# CXX defines
CXX_DEFS =  \
-DSTM32F446xx \
-DUSE_HAL_DRIVER


# AS includes
AS_INCLUDES = \

# C includes
C_INCLUDES =  \
-I-Core/Inc \
-ICore/Inc \
-ICore/Inc/Components \
-ICore/Inc/Components/GUI \
-ICore/Inc/Components/GUI/Elements/common \
-ICore/Inc/Components/GUI/Elements/history \
-ICore/Inc/Components/GUI/Elements/live \
-ICore/Inc/Components/GUI/Screens \
-ICore/Inc/Components/GUI/Tabs \
-ICore/Inc/Drivers \
-ICore/Inc/ESP32 \
-ICore/Inc/Handlers \
-ICore/Inc/Utils \
-ICore/Lib \
-ICore/Lib/LVGL \
-ICore/Lib/LVGL/src \
-ICore/Lib/LVGL/src/core \
-ICore/Lib/LVGL/src/display \
-ICore/Lib/LVGL/src/draw \
-ICore/Lib/LVGL/src/draw/nxp/pxp \
-ICore/Lib/LVGL/src/draw/nxp/vglite \
-ICore/Lib/LVGL/src/draw/renesas/dave2d \
-ICore/Lib/LVGL/src/draw/sdl \
-ICore/Lib/LVGL/src/draw/sw \
-ICore/Lib/LVGL/src/draw/sw/arm2d \
-ICore/Lib/LVGL/src/draw/sw/blend \
-ICore/Lib/LVGL/src/draw/sw/blend/arm2d \
-ICore/Lib/LVGL/src/draw/vg_lite \
-ICore/Lib/LVGL/src/drivers \
-ICore/Lib/LVGL/src/drivers/display/drm \
-ICore/Lib/LVGL/src/drivers/display/fb \
-ICore/Lib/LVGL/src/drivers/display/ili9341 \
-ICore/Lib/LVGL/src/drivers/display/lcd \
-ICore/Lib/LVGL/src/drivers/display/st7735 \
-ICore/Lib/LVGL/src/drivers/display/st7789 \
-ICore/Lib/LVGL/src/drivers/display/st7796 \
-ICore/Lib/LVGL/src/drivers/display/tft_espi \
-ICore/Lib/LVGL/src/drivers/evdev \
-ICore/Lib/LVGL/src/drivers/libinput \
-ICore/Lib/LVGL/src/drivers/nuttx \
-ICore/Lib/LVGL/src/drivers/sdl \
-ICore/Lib/LVGL/src/drivers/windows \
-ICore/Lib/LVGL/src/drivers/x11 \
-ICore/Lib/LVGL/src/font \
-ICore/Lib/LVGL/src/indev \
-ICore/Lib/LVGL/src/layouts \
-ICore/Lib/LVGL/src/layouts/flex \
-ICore/Lib/LVGL/src/layouts/grid \
-ICore/Lib/LVGL/src/libs/barcode \
-ICore/Lib/LVGL/src/libs/bin_decoder \
-ICore/Lib/LVGL/src/libs/bmp \
-ICore/Lib/LVGL/src/libs/ffmpeg \
-ICore/Lib/LVGL/src/libs/freetype \
-ICore/Lib/LVGL/src/libs/fsdrv \
-ICore/Lib/LVGL/src/libs/gif \
-ICore/Lib/LVGL/src/libs/libjpeg_turbo \
-ICore/Lib/LVGL/src/libs/libpng \
-ICore/Lib/LVGL/src/libs/lodepng \
-ICore/Lib/LVGL/src/libs/lz4 \
-ICore/Lib/LVGL/src/libs/qrcode \
-ICore/Lib/LVGL/src/libs/rle \
-ICore/Lib/LVGL/src/libs/rlottie \
-ICore/Lib/LVGL/src/libs/thorvg \
-ICore/Lib/LVGL/src/libs/tiny_ttf \
-ICore/Lib/LVGL/src/libs/tjpgd \
-ICore/Lib/LVGL/src/misc \
-ICore/Lib/LVGL/src/misc/cache \
-ICore/Lib/LVGL/src/osal \
-ICore/Lib/LVGL/src/others/file_explorer \
-ICore/Lib/LVGL/src/others/fragment \
-ICore/Lib/LVGL/src/others/gridnav \
-ICore/Lib/LVGL/src/others/ime \
-ICore/Lib/LVGL/src/others/imgfont \
-ICore/Lib/LVGL/src/others/monkey \
-ICore/Lib/LVGL/src/others/observer \
-ICore/Lib/LVGL/src/others/snapshot \
-ICore/Lib/LVGL/src/others/sysmon \
-ICore/Lib/LVGL/src/others/vg_lite_tvg \
-ICore/Lib/LVGL/src/stdlib \
-ICore/Lib/LVGL/src/stdlib/builtin \
-ICore/Lib/LVGL/src/themes \
-ICore/Lib/LVGL/src/themes/default \
-ICore/Lib/LVGL/src/themes/mono \
-ICore/Lib/LVGL/src/themes/simple \
-ICore/Lib/LVGL/src/tick \
-ICore/Lib/LVGL/src/widgets/animimage \
-ICore/Lib/LVGL/src/widgets/arc \
-ICore/Lib/LVGL/src/widgets/bar \
-ICore/Lib/LVGL/src/widgets/button \
-ICore/Lib/LVGL/src/widgets/buttonmatrix \
-ICore/Lib/LVGL/src/widgets/calendar \
-ICore/Lib/LVGL/src/widgets/canvas \
-ICore/Lib/LVGL/src/widgets/chart \
-ICore/Lib/LVGL/src/widgets/checkbox \
-ICore/Lib/LVGL/src/widgets/dropdown \
-ICore/Lib/LVGL/src/widgets/image \
-ICore/Lib/LVGL/src/widgets/imagebutton \
-ICore/Lib/LVGL/src/widgets/keyboard \
-ICore/Lib/LVGL/src/widgets/label \
-ICore/Lib/LVGL/src/widgets/led \
-ICore/Lib/LVGL/src/widgets/line \
-ICore/Lib/LVGL/src/widgets/list \
-ICore/Lib/LVGL/src/widgets/menu \
-ICore/Lib/LVGL/src/widgets/msgbox \
-ICore/Lib/LVGL/src/widgets/objx_templ \
-ICore/Lib/LVGL/src/widgets/roller \
-ICore/Lib/LVGL/src/widgets/scale \
-ICore/Lib/LVGL/src/widgets/slider \
-ICore/Lib/LVGL/src/widgets/span \
-ICore/Lib/LVGL/src/widgets/spinbox \
-ICore/Lib/LVGL/src/widgets/spinner \
-ICore/Lib/LVGL/src/widgets/switch \
-ICore/Lib/LVGL/src/widgets/table \
-ICore/Lib/LVGL/src/widgets/tabview \
-ICore/Lib/LVGL/src/widgets/textarea \
-ICore/Lib/LVGL/src/widgets/tileview \
-ICore/Lib/LVGL/src/widgets/win \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IFATFS/App \
-IFATFS/Target \
-IMiddlewares/Third_Party/FatFs/src



# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(C_INCLUDES) $(C_DEFS) $(OPTIMIZATION_FLAGS) 

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPTIMIZATION_FLAGS)

CXXFLAGS = $(MCU) $(CXX_DEFS) $(C_INCLUDES) $(OPTIMIZATION_FLAGS)

# Add additional flags
CFLAGS += -Wall -fdata-sections -ffunction-sections 
ASFLAGS += -Wall -fdata-sections -ffunction-sections 
CXXFLAGS += 

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# Output a list file for the compiled source file.
# This is a representative of the source code in assembly
ASSEMBLER_LIST_OUTPUT_FLAG = -Wa,-a,-ad,-alms=$(call add_release_directory,$<,lst)
CFLAGS += $(ASSEMBLER_LIST_OUTPUT_FLAG)
CXXFLAGS += $(ASSEMBLER_LIST_OUTPUT_FLAG)

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F446RETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = \


# Additional LD Flags from config file
ADDITIONALLDFLAGS = -Wl,--print-memory-usage -specs=nano.specs 

LDFLAGS = $(MCU) $(ADDITIONALLDFLAGS) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIRECTORY)/$(TARGET).map,--cref -Wl,--gc-sections

#######################################
# build the application
#######################################
add_release_directory = $(sort $(addprefix $(RELEASE_DIRECTORY)/,$(addsuffix .$(2),$(basename $(subst ../,parent,$(1))))))

REMOVE_DIRECTORY_COMMAND = rm -fR
mkdir_function = mkdir -p $(1)
ifeq ($(OS),Windows_NT)
  convert_to_windows_path = $(strip $(subst /,\,$(patsubst %/,%,$(1))))
  REMOVE_DIRECTORY_COMMAND = cmd /c rd /s /q
  mkdir_function = cmd /e:on /c md $(call convert_to_windows_path,$(1))
endif



OBJECTS = $(call add_release_directory,$(C_SOURCES),o)
OBJECTS += $(call add_release_directory,$(CPP_SOURCES),o)
OBJECTS += $(call add_release_directory,$(ASM_SOURCES),o)
vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.cc $(sort $(dir $(CXX_SOURCES)))
vpath %.cp $(sort $(dir $(CXX_SOURCES)))
vpath %.cxx $(sort $(dir $(CXX_SOURCES)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))
vpath %.c++ $(sort $(dir $(CXX_SOURCES)))
vpath %.C $(sort $(dir $(CXX_SOURCES)))
vpath %.CPP $(sort $(dir $(CXX_SOURCES)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

# the tree of folders which needs to be present based on the object files
BUILD_TREE = $(sort $(dir $(OBJECTS)))

# C build
$(RELEASE_DIRECTORY)/%.o: %.c STM32Make.make | $(BUILD_TREE)
	$(CC) -c $(CFLAGS) $< -o $@

# C++ build 
$(RELEASE_DIRECTORY)/%.o: %.cc STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.cp STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.cxx STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.cpp STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.c++ STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.C STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.CPP STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

#Assembly build
$(RELEASE_DIRECTORY)/%.o: %.s STM32Make.make | $(BUILD_TREE)
	$(AS) -c $(ASFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.S STM32Make.make | $(BUILD_TREE)
	$(AS) -c $(ASFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.sx STM32Make.make | $(BUILD_TREE)
	$(AS) -c $(ASFLAGS) $< -o $@

$(BUILD_DIRECTORY)/$(TARGET).elf: $(OBJECTS) STM32Make.make | $(BUILD_DIRECTORY)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIRECTORY)/%.hex: $(BUILD_DIRECTORY)/%.elf | $(BUILD_DIRECTORY)
	$(HEX) $< $@

$(BUILD_DIRECTORY)/%.bin: $(BUILD_DIRECTORY)/%.elf | $(BUILD_DIRECTORY)
	$(BIN) $< $@

$(BUILD_DIRECTORY)/%.lss: $(BUILD_DIRECTORY)/%.elf | $(BUILD_DIRECTORY)
	$(LSS) $< > $@

$(BUILD_DIRECTORY):
	$(call mkdir_function, $@)

$(BUILD_TREE):
	$(call mkdir_function, $@)

#######################################
# all
#######################################
# default action: build all
all:
	$(BUILD_DIRECTORY)/$(TARGET).elf 
	$(BUILD_DIRECTORY)/$(TARGET).hex 
	$(BUILD_DIRECTORY)/$(TARGET).bin 
	$(BUILD_DIRECTORY)/$(TARGET).lss 


flash: $(BUILD_DIRECTORY)/$(TARGET).elf
	"$(OPENOCD)" -f ./openocd.cfg -c "program $(BUILD_DIRECTORY)/$(TARGET).elf verify reset exit"

#######################################
# erase
#######################################
erase: $(BUILD_DIRECTORY)/$(TARGET).elf
	"$(OPENOCD)" -f ./openocd.cfg -c "init; reset halt; stm32f4x mass_erase 0; exit"

#######################################
# clean up
#######################################
clean:
	$(REMOVE_DIRECTORY_COMMAND) $(BUILD_DIRECTORY)

#######################################
# custom makefile rules
#######################################

	
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIRECTORY)/*.d)

# *** EOF ***