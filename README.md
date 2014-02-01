align
=====

Align text.

Usage
-----

    align [-h] [-r] [-o <output separator>] [-s <string delimiter>] [-u]

Reads from `stdin` and writes to `stdout`.

- `-r`: Align right (default: left)
- `-o <separator>`: Insert `<separator>` in between the columns (default: `" "`)
- `-s <delimiter>`: Use `<delimiter>` as string delimiter (default: `'"'`) (use `-s ""` to ignore strings)
- `-u <column>`: Only align text up to `<column>`

Example
-------

Before:

	static const char *sd_cmd_arg_str[] = {
		[SD_CMD_ADD_LIBRARY] = "add -l %s",
		[SD_CMD_ADD_PLAYLIST] = "add -p %s",
		[SD_CMD_ADD_QUEUE] = "add -q %s",
		[SD_CMD_CLEAR_LIBRARY] = "clear -l",
		[SD_CMD_CLEAR_PLAYLIST] = "clear -p",
		[SD_CMD_CLEAR_QUEUE] = "clear -q",
		[SD_CMD_LOAD] = "load %s",
		[SD_CMD_NEXT] = "player-next",
		[SD_CMD_PAUSE] = "player-pause",
		[SD_CMD_PLAY] = "player-play",
		[SD_CMD_PLAY_FILE] = "player-play %s",
		[SD_CMD_PREV] = "player-prev",
		[SD_CMD_SEEK] = "seek %s",
		[SD_CMD_STOP] = "player-stop",
		[SD_CMD_TOGGLE_REPEAT] = "toggle repeat",
		[SD_CMD_TOGGLE_SHUFFLE] = "toggle shuffle",
		[SD_CMD_VOLUME] = "vol %s",
	};

After:

	static const char *sd_cmd_arg_str[] = {
		[SD_CMD_ADD_LIBRARY]    = "add -l %s",
		[SD_CMD_ADD_PLAYLIST]   = "add -p %s",
		[SD_CMD_ADD_QUEUE]      = "add -q %s",
		[SD_CMD_CLEAR_LIBRARY]  = "clear -l",
		[SD_CMD_CLEAR_PLAYLIST] = "clear -p",
		[SD_CMD_CLEAR_QUEUE]    = "clear -q",
		[SD_CMD_LOAD]           = "load %s",
		[SD_CMD_NEXT]           = "player-next",
		[SD_CMD_PAUSE]          = "player-pause",
		[SD_CMD_PLAY]           = "player-play",
		[SD_CMD_PLAY_FILE]      = "player-play %s",
		[SD_CMD_PREV]           = "player-prev",
		[SD_CMD_SEEK]           = "seek %s",
		[SD_CMD_STOP]           = "player-stop",
		[SD_CMD_TOGGLE_REPEAT]  = "toggle repeat",
		[SD_CMD_TOGGLE_SHUFFLE] = "toggle shuffle",
		[SD_CMD_VOLUME]         = "vol %s",
	};

Vim
---

    vnoremap <leader>c :!align<cr>


`column -t`
-----------

This program differs from `column -t` in the following ways:

- Empty lines aren't deleted.
- The text keeps its indentation.
- You can align right.

License
-------

MIT
