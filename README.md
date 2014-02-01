align
=====

Align text.

[![Build Status](https://travis-ci.org/mahkoh/align.png?branch=master)](https://travis-ci.org/mahkoh/align)

Usage
-----

    align [-h] [-o <output separator>] [-s <string delimiter>] [-u <column>] [format]

Reads from `stdin` and writes to `stdout`.

- `-o <separator>`: Insert `<separator>` in between the columns (default: `" "`)
- `-s <delimiter>`: Use `<delimiter>` as string delimiter (default: `'"'`) (use `-s ""` to ignore strings)
- `-u <column>`: Only align text up to `<column>`
- `format`: A sequence of `<`, `>`, or `=` representing left alignment, right alignment, or centering of the respective column. The character can optionally be prefixed with a non-negative decimal indicating the minimal padding.

Example
-------

Before:

	static const char *sd_cmd_arg_str[] = {
		[SD_CMD_CLEAR_LIBRARY] = "clear -l",
		[SD_CMD_CLEAR_PLAYLIST] = "clear -p",
		[SD_CMD_CLEAR_QUEUE] = "clear -q",
		[SD_CMD_LOAD] = "load %s",
		[SD_CMD_NEXT] = "player-next",
	};

After:

	static const char *sd_cmd_arg_str[] = {
		[SD_CMD_CLEAR_LIBRARY]  = "clear -l",
		[SD_CMD_CLEAR_PLAYLIST] = "clear -p",
		[SD_CMD_CLEAR_QUEUE]    = "clear -q",
		[SD_CMD_LOAD]           = "load %s",
		[SD_CMD_NEXT]           = "player-next",
	};

Before:

    int a = 111; // a
    int aa = 11; // aa
    int aaa = 1; // aaa

After `align "<><"`:

    int   a = 111; // a
    int  aa = 11;  // aa
    int aaa = 1;   // aaa

Note that the last alignment specifier, `<`, is used for all subsequent columns.

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
