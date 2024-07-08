/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:56:31 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 13:56:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/* MAP ERRORS
	1. Read map => In order to get the size (width / height)
		a. Check if empty map.
		b. Open file
		c. Loop to get the size of the map.
	2. Malloc the map
	3. Fill the map =>Same as the first step.
		a. Open the file
		b. Loop to fill our map.
	4. Wall map errors
		a. Check des caractères sur les murs (non autorisés)
		b. x 4 pour réaliser tous les murs !
	5. Map shape errors
		a. Check si la map est carrée (par contre check JB's tickets car
		la map n'est pas toujours carrée mais il faut qd même le check).
	6. Check la sortie de la map (relevant ?)
	7. Check collectibles (relevant ?)
	8. Check player
	9. Char errors on map
	10. Check Floofill errors
		a. Fill the temp map for floodfill
		b. Checking issues on map ways
*/

