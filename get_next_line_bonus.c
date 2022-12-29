/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:18:35 by mben-sal          #+#    #+#             */
/*   Updated: 2022/12/27 20:00:47 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

int	ft_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free(char **dst, char *src, char *to_free)
{
	*dst = src;
	free (to_free);
}

char	*ft_read(int fd, char *save, char *buff)
{
	int		n;

	if (!save)
		save = ft_strdup("");
	n = 1;
	while (n != 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n <= 0)
		{
			free (buff);
			if (save && !*save)
				ft_free(&save, NULL, save);
			return (save);
		}
		buff[n] = '\0';
		ft_free(&save, ft_strjoin(save, buff), save);
		if (ft_line(buff) != -1)
			break ;
	}
	free (buff);
	return (save);
}

char	*ft_save(char **str)
{
	char	*newln;
	int		i;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		newln = ft_substr((*str), 0, i + 1);
		ft_free(str, ft_strdup((*str) + i + 1), *str);
		return (newln);
	}
	if ((*str)[i] == '\0')
	{
		ft_free(&newln, ft_substr((*str), 0, ft_strlen(*str)), *str);
		*str = NULL;
		return (newln);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*buff;
	static char	*save[10240];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (NULL);
	buff = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buff)
	{
		free(buff);
		free (save);
		return (NULL);
	}
	save[fd] = ft_read(fd, save[fd], buff);
	if (!save[fd])
		return (NULL);
	str = ft_save(&save[fd]);
	return (str);
}
