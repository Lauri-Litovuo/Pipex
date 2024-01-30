/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:13:29 by llitovuo          #+#    #+#             */
/*   Updated: 2023/12/27 17:00:15 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Function extracts and returns a line, when newline character
 *  is found from mix_bin.
 * 
 * @param mix_bin The static variable, to which reads are appended.
 * @return char* The next line.
 */

char	*extract_line(char *mix_bin, char *line)
{
	size_t	i;

	i = 0;
	if (!mix_bin[i])
		return (NULL);
	while (mix_bin[i] != '\n' && mix_bin[i] != '\0')
		i++;
	if (mix_bin[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (mix_bin[i] != '\0' && mix_bin[i] != '\n')
	{
		line[i] = mix_bin[i];
		i++;
	}
	if (mix_bin[i] == '\n')
	{
		line[i] = mix_bin[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/**
 * @brief Assigns the residual after a newline char to mix_bin and
 * adjusts the memory for fit.
 * 
 * @param mix_bin The static variable, to which reads are appended.
 * @return char* Returns the address of the residual to be assigned
 * to mix_bin.
 */

char	*save_residual(char	*mix_bin, char *residual)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!mix_bin)
		return (NULL);
	while (mix_bin[i] != '\n' && mix_bin[i] != 0)
		i++;
	if (mix_bin[i] == 0 || ft_strlen_gnl(mix_bin) == i)
		return (free (mix_bin), NULL);
	residual = malloc ((ft_strlen_gnl(mix_bin) - i + 1) * sizeof(char));
	if (!residual)
		return (free (mix_bin), NULL);
	if (mix_bin[i] != '\0' && i < ft_strlen_gnl(mix_bin))
	{
		i++;
		while (mix_bin[i] != '\0')
			residual[j++] = mix_bin[i++];
		residual[j] = '\0';
	}
	free (mix_bin);
	return (residual);
}

/**
 * @brief Function reads file until EOF or '\n' is found.
 * 
 * @param fd File descriptor to read from.
 * @param mix_bin Static variable of appended reads.
 * @return char* Returns the static variable if EOF reached or '\n' found.
 */

char	*read_file(int fd, char *mix_bin)
{
	char		*read_buffer;
	int			bit_read;

	read_buffer = NULL;
	read_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buffer)
		return (free (mix_bin), NULL);
	bit_read = 1;
	while (bit_read != 0 && ft_strchr_gnl(mix_bin, '\n') == NULL)
	{
		bit_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bit_read == -1)
		{
			free (mix_bin);
			free (read_buffer);
			return (NULL);
		}
		read_buffer[bit_read] = '\0';
		mix_bin = ft_strjoin_gnl(mix_bin, read_buffer);
	}
	free (read_buffer);
	return (mix_bin);
}

/**
 * @brief Get the next line from a file (fd). Keeps residual 
 * beyond next-line in static variable
 * 
 * @param fd File descriptor.
 * @return char* Returns a pointer to allocated new line.
 */

char	*get_next_line(int fd)
{
	static char		*mix_bin;
	char			*line;
	char			*residual;

	line = NULL;
	residual = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, mix_bin, 0) < 0)
	{
		free (mix_bin);
		mix_bin = 0;
		return (NULL);
	}
	mix_bin = read_file(fd, mix_bin);
	if (!mix_bin)
	{
		free (mix_bin);
		return (NULL);
	}
	line = extract_line(mix_bin, line);
	mix_bin = save_residual(mix_bin, residual);
	free (residual);
	residual = NULL;
	return (line);
}
