#!/system/bin/sh
print_autosufq_settings(){
REFRESH_RATE=$(dumpsys SurfaceFlinger | grep "refresh-rate" | awk '{printf "%.0f", $3}')
FRAME_DURATION_NS=$(awk "BEGIN {printf \"%.0f\", (1 / $REFRESH_RATE) * 1000000000}")
EARLY_OFFSET=$((FRAME_DURATION_NS * 35 / 100))      
LATE_OFFSET=$((FRAME_DURATION_NS * 70 / 100))       
HALF_OFFSET=$((FRAME_DURATION_NS / 2))               
THRESHOLD_OFFSET=$((FRAME_DURATION_NS * 85 / 100))     
REGION_DURATION=$((FRAME_DURATION_NS * 3 / 10))     
HWC_DURATION=$((FRAME_DURATION_NS * 95 / 100))      
setprop debug.sf.use_phase_offsets_as_durations 1
setprop debug.sf.enable_advanced_sf_phase_offset 1
setprop debug.sf.predict_hwc_composition_strategy 1
setprop debug.sf.enable_cached_set_render_scheduling true
setprop debug.sf.hwc.min.duration $HWC_DURATION
setprop debug.sf.region_sampling_duration_ns $REGION_DURATION
setprop debug.sf.cached_set_render_duration_ns $HALF_OFFSET
setprop debug.sf.region_sampling_period_ns $REGION_DURATION
setprop debug.sf.phase_offset_threshold_for_next_vsync_ns $THRESHOLD_OFFSET
setprop debug.sf.region_sampling_timer_timeout_ns $REGION_DURATION
setprop debug.sf.early.app.duration $EARLY_OFFSET
setprop debug.sf.earlyGl.app.duration $EARLY_OFFSET
setprop debug.sf.early.sf.duration $EARLY_OFFSET
setprop debug.sf.earlyGl.sf.duration $EARLY_OFFSET
setprop debug.sf.early_app_phase_offset_ns $EARLY_OFFSET
setprop debug.sf.early_gl_app_phase_offset_ns $EARLY_OFFSET
setprop debug.sf.early_gl_phase_offset_ns $EARLY_OFFSET
setprop debug.sf.early_phase_offset_ns $EARLY_OFFSET
setprop debug.sf.high_fps_early_app_phase_offset_ns $EARLY_OFFSET
setprop debug.sf.high_fps_early_gl_app_phase_offset_ns $EARLY_OFFSET
setprop debug.sf.high_fps_early_phase_offset_ns $EARLY_OFFSET
setprop debug.sf.high_fps_early_gl_phase_offset_ns $EARLY_OFFSET
setprop debug.sf.high_fps_late_app_phase_offset_ns $LATE_OFFSET
setprop debug.sf.high_fps_late_sf_phase_offset_ns $LATE_OFFSET
setprop debug.sf.late.app.duration $LATE_OFFSET
setprop debug.sf.late.sf.duration $LATE_OFFSET

if [ "$REFRESH_RATE" -ge 90 ]; then
setprop debug.sf.latch_unsignaled 1
setprop debug.sf.auto_latch_unsignaled true
setprop debug.sf.enable_gl_backpressure false
setprop debug.sf.disable_backpressure 1
else
setprop debug.sf.latch_unsignaled 0
setprop debug.sf.auto_latch_unsignaled false
setprop debug.sf.enable_gl_backpressure true
setprop debug.sf.disable_backpressure 0
fi
#optimize debug prop
setprop debug.sf.boot_animation false
setprop debug.sf.edge_extension_shader false
setprop debug.sf.layerdump 0
setprop debug.sf.enable_transaction_tracing false
setprop debug.sf.layer_history_trace false
setprop debug.sf.layer_caching_highlight false
setprop debug.sf.enable_egl_image_tracker false
setprop debug.sf.vsp_trace false
setprop debug.sf.trace_hint_sessions false
setprop debug.sf.vsync_trace_detailed_info false
setprop debug.sf.dump 0
setprop debug.sf.dump.external false
setprop debug.sf.dump.primary false
setprop debug.sf.dump.png 0
setprop debug.sf.dump.enable false
setprop debug.sf.ddms 0
setprop debug.sf.sa_log 0
setprop debug.sf.treble_testing_override false
setprop debug.sf.kernel_idle_timer_update_overlay false
setprop debug.sf.hwc_hotplug_error_via_neg_vsync 0
setprop debug.sf.prime_shader_cache.edge_extension_shader false
setprop debug.sf.prime_shader_cache.hole_punch false
setprop debug.sf.prime_shader_cache.clipped_dimmed_image_layers false
setprop debug.sf.prime_shader_cache.transparent_image_dimmed_layers false
setprop debug.sf.prime_shader_cache.solid_dimmed_layers false
setprop debug.sf.prime_shader_cache.shadow_layers false
setprop debug.sf.prime_shader_cache.image_layers false
setprop debug.sf.prime_shader_cache.image_dimmed_layers false
setprop debug.sf.prime_shader_cache.solid_layers false
setprop debug.sf.prime_shader_cache.clipped_layers false
setprop debug.sf.prime_shader_cache.pip_image_layers false
setprop debug.sf.showupdates 0
setprop debug.sf.showcpu 0
setprop debug.sf.showbackground 0
setprop debug.sf.showfps 0
setprop debug.sf.show_refresh_rate_overlay_spinner 0
setprop debug.sf.show_refresh_rate_overlay_render_rate 0
setprop debug.sf.show_refresh_rate_overlay_in_middle 0
setprop debug.sf.enable_hwc_vds false
setprop debug.sf.gpuoverlay 0
setprop debug.sf.disable_hwc_vds 1
setprop debug.sf.show_predicted_vsync false
setprop debug.sf.luma_sampling 0

}
print_autosufq_settings &
