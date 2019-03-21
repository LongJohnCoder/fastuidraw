# Begin standard header
sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)
# End standard header

dir:= $(d)/shaders
include $(dir)/Rules.mk

FASTUIDRAW_SOURCES += $(call filelist, shader_source.cpp shader_code.cpp \
	painter_item_shader_glsl.cpp painter_blend_shader_glsl.cpp \
	painter_shader_registrar_glsl.cpp \
	unpack_source_generator.cpp)


# Begin standard footer
d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
# End standard footer
