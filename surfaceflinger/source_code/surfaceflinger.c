#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void welcomescreen() {
    FILE *fp = popen("dumpsys SurfaceFlinger | grep 'refresh-rate' | awk '{printf \"%.0f\", $3}'", "r");
    if (!fp) {
        printf("Failed to get refresh rate\n");
        return;
    }

    char buffer[16];
    if (!fgets(buffer, sizeof(buffer), fp)) {
        printf("Error reading refresh rate\n");
        pclose(fp);
        return;
    }
    pclose(fp);

    int refresh_rate = atoi(buffer);
    if (refresh_rate <= 0) {
        printf("Invalid refresh rate: %s\n", buffer);
        return;
    }

    long frame_ns = (1.0 / refresh_rate) * 1000000000;

    printf("\n--- Welcome ---\n");
    printf("Refresh Rate : %d Hz\n", refresh_rate);
    printf("Frame Time   : %ld ns (%.2f ms)\n", frame_ns, frame_ns / 1e6);
    printf("--------------\n\n");
}


void set_autosufq_settings() {
    FILE *fp = popen("dumpsys SurfaceFlinger | grep 'refresh-rate' | awk '{printf \"%.0f\", $3}'", "r");
    if (!fp) {
        fprintf(stderr, "Failed to execute dumpsys command\n");
        return;
    }

    char buffer[16];
    if (!fgets(buffer, sizeof(buffer), fp)) {
        fprintf(stderr, "Failed to read refresh rate\n");
        pclose(fp);
        return;
    }
    pclose(fp);

    int refresh_rate = atoi(buffer);
    if (refresh_rate <= 0) {
        fprintf(stderr, "Invalid refresh rate: %s\n", buffer);
        return;
    }

    // calculate timing offsets
    long frame_duration_ns = (1.0 / refresh_rate) * 1000000000;
    long early_offset = frame_duration_ns * 25 / 100;
    long late_offset = frame_duration_ns * 65 / 100;
    long half_offset = frame_duration_ns / 2;
    long threshold_offset = frame_duration_ns * 85 / 100;
    long region_duration = frame_duration_ns * 2 / 10;
    long hwc_duration = frame_duration_ns * 95 / 100;

    char command[512];

    // set surfaceflinger debug props
    snprintf(command, sizeof(command), "setprop debug.sf.enable_transaction_tracing false"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.layer_history_trace false"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.layer_caching_highlight false"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.enable_egl_image_tracker false"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.vsp_trace false"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.trace_hint_sessions false"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.vsync_trace_detailed_info false"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.treble_testing_override false"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.use_phase_offsets_as_durations 1"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.enable_cached_set_render_scheduling true"); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.hwc.min.duration %ld", hwc_duration); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.region_sampling_duration_ns %ld", region_duration); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.cached_set_render_duration_ns %ld", half_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.region_sampling_period_ns %ld", region_duration); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.phase_offset_threshold_for_next_vsync_ns %ld", threshold_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.region_sampling_timer_timeout_ns %ld", region_duration); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.early.app.duration %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.earlyGl.app.duration %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.early.sf.duration %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.earlyGl.sf.duration %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.early_app_phase_offset_ns %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.early_gl_app_phase_offset_ns %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.early_gl_phase_offset_ns %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.early_phase_offset_ns %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps_early_app_phase_offset_ns %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps_early_gl_app_phase_offset_ns %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps_early_phase_offset_ns %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps_early_gl_phase_offset_ns %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps.early.app.duration %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps.earlyGl.app.duration %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps.early.sf.duration %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps.earlyGl.sf.duration %ld", early_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps_late_app_phase_offset_ns %ld", late_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps_late_sf_phase_offset_ns %ld", late_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps.late.app.duration %ld", late_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.high_fps.late.sf.duration %ld", late_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.late.app.duration %ld", late_offset); system(command);
    snprintf(command, sizeof(command), "setprop debug.sf.late.sf.duration %ld", late_offset); system(command);

    if (refresh_rate >= 90) {
        snprintf(command, sizeof(command), "setprop debug.sf.latch_unsignaled 1"); system(command);
        snprintf(command, sizeof(command), "setprop debug.sf.auto_latch_unsignaled true"); system(command);
        snprintf(command, sizeof(command), "setprop debug.sf.enable_gl_backpressure false"); system(command);
        snprintf(command, sizeof(command), "setprop debug.sf.disable_backpressure 1"); system(command);
    } else {
        snprintf(command, sizeof(command), "setprop debug.sf.latch_unsignaled 0"); system(command);
        snprintf(command, sizeof(command), "setprop debug.sf.auto_latch_unsignaled false"); system(command);
        snprintf(command, sizeof(command), "setprop debug.sf.enable_gl_backpressure true"); system(command);
        snprintf(command, sizeof(command), "setprop debug.sf.disable_backpressure 0"); system(command);
    }
} 

int main() {
    welcomescreen();
    set_autosufq_settings();
    return 0;
}
