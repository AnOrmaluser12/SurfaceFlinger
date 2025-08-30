#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get_refresh_rate() {
    static int cached_rate = -1;
    if (cached_rate > 0) return cached_rate;
    FILE *fp = popen("dumpsys SurfaceFlinger | grep 'refresh-rate' | awk '{printf \"%.0f\", $3}'", "r");
    if (!fp) return -1;
    char buffer[16];
    if (!fgets(buffer, sizeof(buffer), fp)) {
        pclose(fp);
        return -1;
    }
    pclose(fp);
    cached_rate = atoi(buffer);
    return cached_rate;
}

void welcomescreen() {
    int refresh_rate = get_refresh_rate();
    if (refresh_rate <= 0) {
        printf("Invalid refresh rate\n");
        return;
    }
    long frame_ns = (1.0 / refresh_rate) * 1000000000;
    printf("\n--- Welcome ---\nRefresh Rate : %d Hz\nFrame Time   : %ld ns (%.2f ms)\n--------------\n\n", 
           refresh_rate, frame_ns, frame_ns / 1e6);
}

void set_autosufq_settings() {
    int refresh_rate = get_refresh_rate();
    if (refresh_rate <= 0) {
        fprintf(stderr, "Invalid refresh rate\n");
        return;
    }
    long frame_duration_ns = (1.0 / refresh_rate) * 1000000000;
    long early_offset = frame_duration_ns * 30 / 100;
    long early_gl_offset = frame_duration_ns * 30 / 100;
    long early_glapp_offset = frame_duration_ns * 35 / 100;
    long late_offset = frame_duration_ns * 70 / 100;
    long half_offset = frame_duration_ns / 2;
    long threshold_offset = frame_duration_ns * 85 / 100;
    long region_duration = frame_duration_ns * 20 / 10;
    long hwc_duration = frame_duration_ns * 95 / 100;
    char command[4096];
    snprintf(command, sizeof(command),
        "setprop debug.sf.enable_transaction_tracing false && "
        "setprop debug.sf.layer_history_trace false && "
        "setprop debug.sf.layer_caching_highlight false && "
        "setprop debug.sf.enable_egl_image_tracker false && "
        "setprop debug.sf.vsp_trace false && "
        "setprop debug.sf.trace_hint_sessions false && "
        "setprop debug.sf.vsync_trace_detailed_info false && "
        "setprop debug.sf.treble_testing_override false && "
        "setprop debug.sf.use_phase_offsets_as_durations 1 && "
        "setprop debug.sf.enable_cached_set_render_scheduling true && "
        "setprop debug.sf.hwc.min.duration %ld && "
        "setprop debug.sf.region_sampling_duration_ns %ld && "
        "setprop debug.sf.cached_set_render_duration_ns %ld && "
        "setprop debug.sf.region_sampling_period_ns %ld && "
        "setprop debug.sf.phase_offset_threshold_for_next_vsync_ns %ld && "
        "setprop debug.sf.region_sampling_timer_timeout_ns %ld && "
        "setprop debug.sf.early.app.duration %ld && "
        "setprop debug.sf.earlyGl.app.duration %ld && "
        "setprop debug.sf.early.sf.duration %ld && "
        "setprop debug.sf.earlyGl.sf.duration %ld && "
        "setprop debug.sf.early_app_phase_offset_ns %ld && "
        "setprop debug.sf.early_gl_app_phase_offset_ns %ld && "
        "setprop debug.sf.early_gl_phase_offset_ns %ld && "
        "setprop debug.sf.early_phase_offset_ns %ld && "
        "setprop debug.sf.high_fps_early_app_phase_offset_ns %ld && "
        "setprop debug.sf.high_fps_early_gl_app_phase_offset_ns %ld && "
        "setprop debug.sf.high_fps_early_phase_offset_ns %ld && "
        "setprop debug.sf.high_fps_early_gl_phase_offset_ns %ld && "
        "setprop debug.sf.high_fps.early.app.duration %ld && "
        "setprop debug.sf.high_fps.earlyGl.app.duration %ld && "
        "setprop debug.sf.high_fps.early.sf.duration %ld && "
        "setprop debug.sf.high_fps.earlyGl.sf.duration %ld && "
        "setprop debug.sf.high_fps_late_app_phase_offset_ns %ld && "
        "setprop debug.sf.high_fps_late_sf_phase_offset_ns %ld && "
        "setprop debug.sf.high_fps.late.app.duration %ld && "
        "setprop debug.sf.high_fps.late.sf.duration %ld && "
        "setprop debug.sf.late.app.duration %ld && "
        "setprop debug.sf.late.sf.duration %ld && "
        "setprop debug.sf.latch_unsignaled %d && "
        "setprop debug.sf.auto_latch_unsignaled %s && "
        "setprop debug.sf.enable_gl_backpressure %s && "
        "setprop debug.sf.disable_backpressure %d",
        hwc_duration, region_duration, half_offset, region_duration, threshold_offset, region_duration,
        early_offset, early_glapp_offset, early_offset, early_gl_offset, early_offset, early_glapp_offset,
        early_gl_offset, early_offset, early_offset, early_glapp_offset, early_offset, early_gl_offset,
        early_offset, early_glapp_offset, early_offset, early_gl_offset, late_offset, late_offset,
        late_offset, late_offset, late_offset, late_offset,
        refresh_rate >= 90 ? 1 : 0, refresh_rate >= 90 ? "true" : "false",
        refresh_rate >= 90 ? "false" : "true", refresh_rate >= 90 ? 1 : 0);
    system(command);
}

int main() {
    welcomescreen();
    set_autosufq_settings();
    return 0;
}
