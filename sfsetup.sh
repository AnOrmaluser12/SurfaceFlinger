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
}
print_autosufq_settings &