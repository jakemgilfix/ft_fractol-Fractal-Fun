/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:58:55 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/24 10:23:30 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** BONUSES *********************************************************************
** ~ ft_dprintf()        :   `dprintf()` clone; like `printf()`, but writes   **
**                              to a file descriptor.                         **
** ~ Bufferized output   :   Output is bufferized before being printed,       **
**                              resulting in better speed. Buffer size is     **
**                              user-definable.                               **
** ~ Colors              :   Implements %{color} conversions, where 'color'   **
**                              can be 'red', 'green', 'blue', 'cyan',        **
**                              'magenta', 'yellow', or 'nocolor'.            **
** ~ Asterisk (*)        :   Implements * width/precision specifier, which    **
**                           uses user-provided argument from argument list   **
**                           as width or precision specification.             **
** ~ Binary conversions  :   Implements %b conversions, supporting all the    **
**                              flags/options that %x/%X/etc. support.        **
** ~ Extended sizes      :   Implements `j` (intmax_t) and `z` (size_t) size  **
**                              specifiers.                                   **
** ~ Comments            :   Good comments should be a bonus.                 **
********************************************************************************
*/

/*
** INCLUDES ********************************************************************
** stdarg.h     :   va_list, va_start, va_arg                                 **
** inttypes.h   :   uintmax_t, intmax_t                                       **
********************************************************************************
*/

# include <stdarg.h>
# include <inttypes.h>

/*
** MACROS **********************************************************************
** FTPF_BUFF_SIZE   :   Size of the `ft_*printf()` buffer                     **
** COLORS           :   Red, green, blue, cyan, magenta, yellow, and no color **
********************************************************************************
*/

# define FTPF_BUFF_SIZE	4096

# define C_RED			"\033[31m"
# define C_GREEN		"\033[32m"
# define C_BLUE			"\033[34m"
# define C_CYAN			"\033[36m"
# define C_MAGENTA		"\033[35m"
# define C_YELLOW		"\033[33m"
# define C_NOCOL		"\033[0m"

/*
** PRINTF CONVERSION SPECIFICATION FLAGS/PARAMETERS ****************************
**                   ~ Reference: https://bit.ly/2Nutfut ~                    **
**                                                                            **
** ~ A conversion specification consists of [optional] and required fields in **
**   this form:      %[flags][width][.precision][size]type                    **
**                                                                            **
** FLAG DIRECTIVES (zero or more may appear):                                 **
**   FL_MINUS     '-'  left align the result within the given field width     **
**                     (default: right-align)                                 **
**   FL_PLUS      '+'  use a sign (+/-) to prefix the output value if it is   **
**                     of a signed type (default: only show -)                **
**   FL_ZERO      '0'  if `width` is prefixed by '0', leading zeros are added **
**                     until the min. width is reached. If both '0' and '-'   **
**                     appear, '0' is IGNORED. If '0' is specified for an     **
**                     integer format (i/u/x/X/o/d) AND a `precision` spec.   **
**                     is ALSO present, '0' is IGNORED.                       **
**   FL_BLANK     ' '  Use a blank to prefix the output value if it is both   **
**                     signed and positive. If both ' ' and '+' flags are     **
**                     present, ' ' is IGNORED.                               **
**   FL_HASH      '#'  When used with o/x/X format, the '#' flag uses 0, 0x,  **
**                     or 0X to prefix any non-zero output value.             **
** OTHER FLAGS:                                                               **
**    FL_PREC      :   Whether the user specified a `precision`               **
**    FL_UPPER     :   Uppercase output is desired (e.g., with %X)            **
**    FL_POINTER   :   Whether the specified `type` is 'p'                    **
********************************************************************************
*/

# define FL_MINUS	1
# define FL_PLUS	2
# define FL_ZERO	4
# define FL_BLANK	8
# define FL_HASH	16

# define FL_PREC	32
# define FL_UPPER	64
# define FL_POINTER	128

/*
** DATA TYPES ******************************************************************
** t_sz_spec        :   (optional) `size` specified in conversion spec.       **
** t_printf_spec    :                                                         **
**     fd           :   file descriptor to which to write the output          **
**     ap           :   list of additional arguments given to `ft_*printf()`  **
**     format       :   format string provided as argument to `ft_*printf()`  **
**     buffer       :   output buffer                                         **
**     buffer_idx   :   current index in `buffer`                             **
**     char_count   :   number of characters printed by `ft_*printf()`        **
**     flags        :   conversion flags                                      **
**     width        :   minimum length of output (optional part of conv spec) **
**     prec         :   precision specified (or not) by conversion specifier  **
**     size         :   argument length modifier for the `type` conv. spec.   **
**     type         :   conversion type (e.g., 'i'/'o'/'u'/'x'/'X')           **
**     padding      :   amount of padding needed                              **
**     printed      :   number of characters printed                          **
********************************************************************************
*/

typedef enum
{
	sz_default,
	sz_hh,
	sz_h,
	sz_l,
	sz_L,
	sz_ll,
	sz_j,
	sz_z
}	t_sz_spec;

typedef struct	s_printf_spec
{
	int			fd;
	va_list		ap;
	char		*format;
	char		buffer[FTPF_BUFF_SIZE];
	int			buffer_idx;
	int			char_count;
	char		flags;
	int			width;
	int			prec;
	t_sz_spec	size;
	char		type;
	int			padding;
	int			printed;
}				t_printf_spec;

/*
********************************************************************************
**                                  BUFFER.C                                  **
** ftpf_buffer()       :   Puts string `to_add` into the print buffer. If the **
**                           buffer fills up, it's printed to `spec->fd`.     **
** ftpf_putpadding()   :   Puts `spec->padding` many `c`s into the buffer.    **
********************************************************************************
*/

void			ftpf_buffer(t_printf_spec *spec, char *to_add, int size);
void			ftpf_putpadding(t_printf_spec *spec, char c);

/*
********************************************************************************
**                                FT_PRINTF.C                                 **
** ft_printf()    :   This is what you're here for, presumably.               **
** ft_dprintf()   :   Same as `ft_printf()`, but prints to a file descriptor. **
********************************************************************************
*/

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);

/*
********************************************************************************
**                               HANDLE_ASCII.C                               **
** ftpf_putchar()   :   Handles conversion of 'c' `type`.                     **
** ftpf_putstr()    :   Handles conversion of 's' `type`.                     **
********************************************************************************
*/

void			ftpf_putchar(t_printf_spec *spec, unsigned int c);
void			ftpf_putstr(t_printf_spec *spec);

/*
********************************************************************************
**                               HANDLE_FLOAT.C                               **
** ftpf_putfloat()   :   Handles conversion of 'f' `type`.                    **
********************************************************************************
*/

void			ftpf_putfloat(t_printf_spec *spec);

/*
********************************************************************************
**                                HANDLE_INT.C                                **
** ftpf_putnum()        :   Handles conversion of 'd'/'i' `type`s.            **
** ftpf_putnum_base()   :   Handles conversion of 'b'/'o'/'u'/'x'/'X'         **
**                          `type`s, as well as 'p'.                          **
** ftpf_itoa_base()     :   Puts `n` (in base `base`) into the print buffer,  **
**                          formatted according given conversion spec. Would  **
**                          otherwise be static, but is also used by          **
**                          ftpf_putptr() (in handle_ptr.c).                  **
********************************************************************************
*/

void			ftpf_putnum(t_printf_spec *spec);
void			ftpf_putnum_base(int base, t_printf_spec *spec);
void			ftpf_itoa_base(uintmax_t n, int base, t_printf_spec *spec);

/*
********************************************************************************
**                                HANDLE_PTR.C                                **
** ftpf_putptr()   :   Handles conversion of 'p' `type`.                      **
********************************************************************************
*/

void			ftpf_putptr(t_printf_spec *spec);

/*
********************************************************************************
**                                  PARSER.C                                  **
** parse_format()   :   Parses the format string and (optional) additional    **
**                      arguments given to `ft_printf()`. This is the actual  **
**                      workhorse.                                            **
********************************************************************************
*/

int				parse_format(t_printf_spec *spec);

/*
********************************************************************************
**                                 PARSER2.C                                  **
** ftpf_finish_conversion()   :   Parses the `type` parameter given as part   **
**                                of a conversion specification and finishes  **
**                                the conversion, calling the appropriate     **
**                                handling function.                          **
********************************************************************************
*/

void			ftpf_finish_conversion(t_printf_spec *spec);

#endif
