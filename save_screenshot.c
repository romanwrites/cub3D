/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 12:24:58 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/30 12:25:11 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned char		*create_bmp_file_header(int height, int stride)
{
	int						file_size;
	static unsigned char	file_header[FILE_HEADER_SIZE];

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

	return (file_header);
}

static unsigned char		*create_bmp_info_header(int height, int width)
{
	static unsigned char	info_header[INFO_HEADER_SIZE];

	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(width);
	info_header[5] = (unsigned char)(width >> 8);
	info_header[6] = (unsigned char)(width >> 16);
	info_header[7] = (unsigned char)(width >> 24);
	info_header[8] = (unsigned char)(height);
	info_header[9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(BYTES_PER_PIXEL * 8);

	return (info_header);
}

static void					write_bmp(t_game *sv, int y, int fd)
{
	int						width_in_bytes;
	int						padding_size;
	int						stride;
	static unsigned char	padding[3] = {0, 0, 0};

	y = 0;
	width_in_bytes = sv->map.res_w * BYTES_PER_PIXEL;

	padding_size = (4 - (width_in_bytes) % 4) % 4;
	stride = (width_in_bytes) + padding_size;
	write(fd, create_bmp_file_header(sv->map.res_h, stride), \
			FILE_HEADER_SIZE);
	write(fd, create_bmp_info_header(-sv->map.res_h, sv->map.res_w), \
			INFO_HEADER_SIZE);
	while (y < sv->map.res_h)
	{
		write(fd, sv->img.addr + (y * sv->img.line_length), \
				sv->img.line_length);
		write(fd, padding, padding_size);
		++y;
	}
}

int							save_screenshot(t_game *sv, char *map_name)
{
	int						fd;
	char					*filename;

	filename = ft_strjoin(map_name, ".bmp");
	ft_alloc_check(filename);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC | \
						S_IRUSR | S_IWUSR | S_IROTH, 0644);
	if (fd == -1)
		exit_with_error_message("Create screenshot failure. fd == -1");
	write_bmp(sv, 0, fd);
	close(fd);
	free(filename);
	return (0);
}