/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:18:35 by mben-sal          #+#    #+#             */
/*   Updated: 2022/12/18 15:55:26 by mben-sal         ###   ########.fr       */
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

char	*ft_read(int fd, char *save )
{
	int		n;
	char	*buff;

	if (!save)
		save = ft_strdup("");
	buff = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	n = 1;
	while (n != 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[n] = '\0';
		save = ft_strjoin(save, buff);
		if (ft_line(save) != -1)
			break ;
	}
	free (buff);
	return (save);
}

char	*ft_save_line(char*save)
{
	int		i;
	char	*line;

	i = 0;
	while (save[i] && save[i] != '\n')
	{
		i++;
	}
	line = ft_substr (save, 0, i +1);
	if (save[i] == '\0')
		return (NULL);
	return (line);
}

char	*ft_save(char *s, char *str)
{
	int		i;
	char	*tmp;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str);
	tmp = ft_strdup(s + i);
	free (s);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*save [1027];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1027)
		return (NULL);
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	str = ft_save_line(save[fd]);
	save[fd] = ft_save(save[fd], str);
	free (save[fd]);
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