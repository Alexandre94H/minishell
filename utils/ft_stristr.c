/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stristr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:03:17 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/31 11:06:15 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_stristr(char *str, char *value)
{
	int	index;
	int index1;

	index = 0;
	while (str[index])
	{
		if (str[index] == *value)
		{
			index1 = 0;
			while (value[index1] && str[index + index1] == value[index1])
				index1++;
			if (!value[index1])
				return (index);
			index += index1;
		}
		else
			index++;
	}
	return (-1);
}