/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:18:35 by mben-sal          #+#    #+#             */
/*   Updated: 2022/12/23 18:43:29 by mben-sal         ###   ########.fr       */
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

void	ft_assign(char **dst, char *src, char *to_free)
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
	while (n != 0 || (ft_line(buff) != -1))
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n <= 0)
		{
			free (buff);
			if (save && !*save)
				ft_assign(&save, NULL, save);
			return (save);
		}
		buff[n] = '\0';
		ft_assign(&save, ft_strjoin(save, buff), save);
	}
	free (buff);
	return (save);
}

char	*ft_save(char **saved)
{
	char	*line;
	int		i;

	i = 0;
	while ((*saved)[i] != '\n' && (*saved)[i] != '\0')
		i++;
	if ((*saved)[i] == '\n')
	{
		line = ft_substr((*saved), 0, i + 1);
		ft_assign(saved, ft_strdup((*saved) + i + 1), *saved);
		return (line);
	}
	if ((*saved)[i] == '\0')
	{
		ft_assign(&line, ft_substr((*saved), 0, ft_strlen(*saved)), *saved);
		*saved = NULL;
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*buff;
	static char	*save[1027];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1027)
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

// int main()
// {
// 	int i = 0;
// 	int j = 0;
// 	char *s;
// 	int fd [3];

// 	fd[0] = open("test" , O_CREAT | O_RDWR);
// 	fd[1] = open("test1" , O_CREAT | O_RDWR);
// 	fd[2] = open("test2" , O_CREAT | O_RDWR);

// 	while (i <= 5 && j <= 3)
// 	{
// 		s = get_next_line(fd[j]);
// 		if(!s)
// 			return 0;
// 		printf("%s",s);
// 		i++;
// 		j++;
// 	}
// 	return 0;
// }
