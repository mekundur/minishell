/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_delim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:55:45 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/23 13:44:12 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char *ft_get_delim(char *file)
{
    char    *delim;
    int     i = 0;
    int     j = 0;
    bool    in_quotes = false;
    bool    found_start = false;
    char    quote_char = '\0';
    
    // Skip initial whitespace
    while (file[i] && ft_is_whitespace(file[i]))
        i++;
        
    int start = i;
    // Find the end of the delimiter
    while (file[i])
    {
        // Handle start of quotes
        if ((file[i] == '"' || file[i] == '\'') && (!in_quotes))
        {
            in_quotes = true;
            quote_char = file[i];
            if (!found_start)
                start = i + 1;
            found_start = true;
            i++;
            continue;
        }
        
        // Handle end of quotes
        if (file[i] == quote_char && in_quotes)
        {
            in_quotes = false;
            break;
        }
        
        // Break on redirect or pipe if not in quotes
        if (!in_quotes && (file[i] == '<' || file[i] == '>' || file[i] == '|'))
            break;
            
        // If not in quotes and haven't found start yet, handle start
        if (!in_quotes && !found_start && !ft_is_whitespace(file[i]))
            found_start = true;
            
        // Break on whitespace only if not in quotes and after content
        if (!in_quotes && found_start && ft_is_whitespace(file[i]))
            break;
            
        i++;
    }
    
    // Calculate end position
    int end = i;
    if (in_quotes) // If still in quotes, go to end of content
        while (file[end] && file[end] != quote_char)
            end++;
            
    // Go back to remove trailing whitespace if not in quotes
    if (!in_quotes)
        while (end > start && ft_is_whitespace(file[end - 1]))
            end--;
            
    // If we started with a quote, adjust start position
    if (file[start] == '"' || file[start] == '\'')
        start++;
        
    // Allocate and copy
    delim = (char *)malloc((end - start + 1) * sizeof(char));
    if (!delim)
        return NULL;
        
    // Copy content
    while (start < end)
        delim[j++] = file[start++];
        
    delim[j] = '\0';
    return delim;
}