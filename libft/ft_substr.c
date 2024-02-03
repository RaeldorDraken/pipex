/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:23:38 by eros-gir          #+#    #+#             */
/*   Updated: 2022/06/09 10:53:59 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	lo;
	size_t	lr;
	size_t	maxlo;
	char	*sr;

	lo = start;
	maxlo = ft_strlen(s);
	lr = 0;
	if (!s || maxlo <= lo)
		return (ft_strdup(""));
	if (len >= maxlo)
		len = maxlo;
	sr = ft_calloc(sizeof(char), len + 1);
	if (!sr)
		return (0);
	while (lr < len && lo < maxlo)
		sr[lr++] = s[lo++];
	sr[lr] = '\0';
	return (sr);
}
