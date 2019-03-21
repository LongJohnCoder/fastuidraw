/*!
 * \file painter_surface_gl_private.hpp
 * \brief file painter_surface_gl_private.hpp
 *
 * Copyright 2016 by Intel.
 *
 * Contact: kevin.rogovin@intel.com
 *
 * This Source Code Form is subject to the
 * terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with
 * this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * \author Kevin Rogovin <kevin.rogovin@intel.com>
 *
 */

#pragma once

#include <fastuidraw/gl_backend/painter_backend_gl.hpp>
#include <fastuidraw/gl_backend/ngl_header.hpp>

namespace fastuidraw { namespace gl { namespace detail {

class SurfaceGLPrivate:noncopyable
{
public:
  enum fbo_tp_bits
    {
      fbo_color_buffer_bit,
      fbo_num_bits,

      fbo_color_buffer = FASTUIDRAW_MASK(fbo_color_buffer_bit, 1),

      number_fbo_t = FASTUIDRAW_MASK(0, fbo_num_bits) + 1
    };

  enum immediate_coverage_buffer_fmt_t
    {
      immediate_coverage_buffer_fmt_u8,
      immediate_coverage_buffer_fmt_u32,

      number_immediate_coverage_buffer_fmt_t
    };

  explicit
  SurfaceGLPrivate(enum PainterSurface::render_type_t type,
                   GLuint texture, ivec2 dimensions);

  ~SurfaceGLPrivate();

  static
  PainterBackendGL::SurfaceGL*
  surface_gl(const reference_counted_ptr<PainterSurface> &surface);

  GLuint
  immediate_coverage_buffer(enum immediate_coverage_buffer_fmt_t tp);

  static
  GLenum
  auxiliaryBufferInternalFmt(enum immediate_coverage_buffer_fmt_t tp)
  {
    return tp == immediate_coverage_buffer_fmt_u8 ?
      GL_R8 :
      GL_R32UI;
  }

  GLuint
  color_buffer(void)
  {
    return buffer(buffer_color);
  }

  c_array<const GLenum>
  draw_buffers(uint32_t tp);

  GLuint
  fbo(enum PainterBackendGL::blending_type_t blending)
  {
    return fbo(fbo_bits(blending));
  }

  GLuint
  fbo(uint32_t tp);

  c_array<const GLenum>
  draw_buffers(enum PainterBackendGL::blending_type_t blending)
  {
    return draw_buffers(fbo_bits(blending));
  }

  reference_counted_ptr<const Image>
  image(const reference_counted_ptr<ImageAtlas> &atlas);

  enum PainterSurface::render_type_t m_render_type;
  PainterSurface::Viewport m_viewport;
  vec4 m_clear_color;
  ivec2 m_dimensions;

private:
  enum buffer_t
    {
      buffer_color,
      buffer_depth,

      number_buffer_t
    };

  uint32_t
  fbo_bits(enum PainterBackendGL::blending_type_t blending);

  GLuint
  buffer(enum buffer_t);

  vecN<GLuint, number_immediate_coverage_buffer_fmt_t> m_immediate_coverage_buffer;
  vecN<GLuint, number_buffer_t> m_buffers;
  vecN<GLuint, number_fbo_t> m_fbo;
  vecN<vecN<GLenum, 1>, number_fbo_t> m_draw_buffer_values;
  vecN<c_array<const GLenum>, number_fbo_t> m_draw_buffers;
  reference_counted_ptr<const Image> m_image;

  bool m_own_texture;
};

}}}
