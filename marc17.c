#include "marc8.h"

/**
 * is_cmad - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmad(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupl_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dupl_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds this cmad in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmad: the cmad to find
 *
 * Return: full path of cmad if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmad)
{
	int i = 0, curr_pos = 0;
	char *path;
	
	if (!pathstr)
		return (NULL);
	if ((_strlen(cmad) > 2) && starts_with(cmad, "./"))
	{
		if (is_cmad(info, cmad))
			return (cmad);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == 'i')
		{
			path = dupl_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmad);
			else
			{
				_strcat(path, "/");
				_strrcat(path, cmad);
			}
			if (is_cmad(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
