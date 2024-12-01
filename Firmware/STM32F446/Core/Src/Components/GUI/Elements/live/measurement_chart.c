#include "measurement_chart.h"

MeasurementChart MeasurementChart_create(MeasurementChart_Config * config) {
    MeasurementChart chartInstance = {};

    lv_obj_t * chart = lv_chart_create(config->screen);

    lv_obj_align(chart, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_size(chart, 250, 128);
    lv_obj_set_pos(chart, config->x + 50, config->y);
    lv_obj_set_style_bg_color(chart, lv_color_hex(config->mainColor), LV_PART_MAIN);
    lv_obj_set_style_border_color(chart, lv_color_hex(0x000000), LV_PART_MAIN);

    lv_obj_t * titleLabel = lv_label_create(chart);

    lv_obj_set_style_text_color(titleLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(titleLabel, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_pos(titleLabel, 0, -5);
    lv_obj_set_width(titleLabel, 160);
    lv_obj_set_style_text_align(titleLabel, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);
    lv_label_set_text(titleLabel, config->title);

    lv_chart_series_t * series =
        lv_chart_add_series(chart, lv_color_hex(config->series1Color), LV_CHART_AXIS_PRIMARY_Y);

    lv_chart_set_next_value(chart, series, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_x_start_point(chart, series, 1);
    lv_chart_set_point_count(chart, 20);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 50, 110);

    // Vertical scale
    lv_obj_t * verticalScale = lv_scale_create(config->screen);

    lv_scale_set_mode(verticalScale, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_obj_set_size(verticalScale, 45, 120);
    lv_obj_set_pos(verticalScale, config->x, config->y);
    lv_scale_set_total_tick_count(verticalScale, 7);
    lv_scale_set_major_tick_every(verticalScale, 1);
    lv_obj_set_style_pad_left(verticalScale, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_top(verticalScale, 10, LV_PART_MAIN);
    lv_obj_set_style_text_color(verticalScale, lv_color_hex(config->mainColor), LV_PART_MAIN);

    static const char * rpms[] = {"50", "60", "70", "80", "90", "100", "110", NULL};
    lv_scale_set_text_src(verticalScale, rpms);

    lv_chart_refresh(chart);

    chartInstance.chart  = chart;
    chartInstance.series = series;

    return chartInstance;
}

void MeasurementChart_setValue(MeasurementChart * instance, uint32_t value1) {
    lv_chart_set_next_value(instance->chart, instance->series, value1);

    lv_chart_refresh(instance->chart);
}