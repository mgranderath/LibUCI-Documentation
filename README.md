# LibUCI-Documentation
Documentation for the libuci c interface

### `struct uci_context *uci_alloc_context(void)`

__Purpose__: Allocate a new UCI context

### `void uci_free_context(struct uci_context *ctx)`

__Purpose__: Free the allocated UCI context, including all of its data

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `uci_context` | the uci context to be deallocated |

### `void uci_perror(struct uci_context *ctx, const char *str)`

__Purpose__: Print the last uci error that occured

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `str` | string to print before the error message |

### `void uci_get_errorstr(struct uci_context *ctx, char **dest, const char *str)`

__Purpose__: Get an error string for the last uci error

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `dest` | target pointer for the string |
| `str` |  prefix for the error message |

__Note__: string must be freed by the caller

### `int uci_import(struct uci_context *ctx, FILE *stream, const char *name, struct uci_package **package, bool single)`

__Purpose__: Import uci config data from a stream

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `stream` | file stream to import from |
| *optional*: `name` |  assume the config has the given name |
| *optional*: `package` | store the last parsed config package in this variable |
| `single` | ignore the 'package' keyword and parse everything into a single package |

##### Notes

- The name parameter is for config files that don't explicitly use the 'package <...>' keyword
- if 'package' points to a non-null struct pointer, enable delta tracking and merge

### `int uci_export(struct uci_context *ctx, FILE *stream, struct uci_package *package, bool header)`

__Purpose__: Export one or all uci config packages

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `stream` | file stream to output to |
| *optional*: `package` | uci config package to export |
| `header` |  include the package header |

### `int uci_load(struct uci_context *ctx, const char *name, struct uci_package **package)`

__Purpose__: Parse an uci config file and store it in the uci context

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `name` | name of the config file (relative to the config directory) |
| `package` | store the loaded config package in this variable |

### `int uci_unload(struct uci_context *ctx, struct uci_package *p)`

__Purpose__: Unload a config file from the uci context

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `package` | pointer to the uci_package struct |

### `int uci_lookup_ptr(struct uci_context *ctx, struct uci_ptr *ptr, char *str, bool extended)`

__Purpose__: Split an uci tuple string and look up an element tree

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `ptr` | lookup result struct (OUT) |
| `str` | uci tuple string to look up (IN) |
| `extended` | allow extended syntax lookup (IN) |

##### Notes

if extended is set to true, uci_lookup_ptr supports the following extended syntax:

__Examples__:
```
network.@interface[0].ifname ('ifname' option of the first interface section)
network.@interface[-1] (last interface section)
```

- uci_lookup_ptr will automatically load a config package if necessary
@str must not be constant, as it will be modified and used for the strings inside @ptr, thus it must also be available as long as @ptr is in use.

### `int uci_add_section(struct uci_context *ctx, struct uci_package *p, const char *type, struct uci_section **res)`

__Purpose__: Add an unnamed section

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `p` | package to add the section to |
| `type` | the section type |
| `res` | pointer to store a reference to the new section in |

### `int uci_set(struct uci_context *ctx, struct uci_ptr *ptr)`

__Purpose__: Set an element's value; create the element if necessary

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `ptr` | uci pointer |

##### Notes

- The updated/created element is stored in `ptr->last`

### `int uci_add_list(struct uci_context *ctx, struct uci_ptr *ptr)`

__Purpose__: Append a string to an element list

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `ptr` | uci pointer with value |

##### Notes

- if the given option already contains a string value, it will be converted to an 1-element-list before appending the next element

### `int uci_reorder_section(struct uci_context *ctx, struct uci_section *s, int pos)`

__Purpose__: Reposition a section

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `s` | uci section to reposition |
| `pos` | new position in the section list |

### `int uci_rename(struct uci_context *ctx, struct uci_ptr *ptr)`

__Purpose__: Rename an element

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `ptr` | uci pointer with value |

### `int uci_delete(struct uci_context *ctx, struct uci_ptr *ptr)`

__Purpose__: Delete a section or option

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `ptr` | uci pointer with value |

### `int uci_save(struct uci_context *ctx, struct uci_package *p)`

__Purpose__: save change delta for a package

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `p` | uci package struct |

### `int uci_commit(struct uci_context *ctx, struct uci_package **p, bool overwrite)`

__Purpose__: commit changes to a package

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `p` | uci package struct pointer |
| `overwrite` | overwrite existing config data and flush delta |

##### Notes

- Committing may reload the whole uci_package data, the supplied pointer is updated accordingly

### `int uci_list_configs(struct uci_context *ctx, char ***list)`

__Purpose__: List available uci config files

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `list` | pointer to list output |

##### Notes

- Caller is responsible for freeing the allocated memory behind list

### `int uci_set_savedir(struct uci_context *ctx, const char *dir)`

__Purpose__: override the default delta save directory

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `dir` | directory name |

### `int uci_add_delta_path(struct uci_context *ctx, const char *dir)`

__Purpose__: add a directory to the search path for change delta files

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `dir` | directory name |

##### Notes

- This function allows you to add directories, which contain 'overlays' for the active config, that will never be committed.

### `int uci_revert(struct uci_context *ctx, struct uci_ptr *ptr)`

__Purpose__: revert all changes to a config item

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `ptr` | uci pointer |

### `int uci_parse_argument(struct uci_context *ctx, FILE *stream, char **str, char **result)`

__Purpose__: parse a shell-style argument, with an arbitrary quoting style

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `stream` | input stream |
| `str` | pointer to the current line (use NULL for parsing the next line) |
| `result` | pointer for the result |

### `int uci_set_backend(struct uci_context *ctx, const char *name)`

__Purpose__: change the default backend

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `name` | name of the backend |

##### Notes

- The default backend is "file", which uses /etc/config for config storage

### `bool uci_validate_text(const char *str)`

__Purpose__: validate a value string for uci options

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `str` | the string to be validated |

### `int uci_add_hook(struct uci_context *ctx, const struct uci_hook_ops *ops)`

__Purpose__: add a uci hook

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `ops` | uci hook ops |

### `int uci_remove_hook(struct uci_context *ctx, const struct uci_hook_ops *ops)`

__Purpose__: remove a uci hook

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `ops` | uci hook ops |

### `int uci_load_plugin(struct uci_context *ctx, const char *filename)`

__Purpose__: load an uci plugin

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `filename` | path to the uci plugin |

##### Notes

- plugin will be unloaded automatically when the context is freed

### `int uci_load_plugins(struct uci_context *ctx, const char *pattern)`

__Purpose__: Load all plugins from a directory

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| *optional*: `filename` | pattern of uci plugin files |

##### Notes

- if pattern is NULL, then uci_load_plugins will call uci_load_plugin for uci_*.so in <prefix>/lib/
  
### `int uci_parse_ptr(struct uci_context *ctx, struct uci_ptr *ptr, char *str)`

__Purpose__: parse a uci string into a uci_ptr

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `ptr` | target data structure |
| `str` | string to parse |

##### Notes

- `str` is modified by this call

### `int uci_lookup_next(struct uci_context *ctx, struct uci_element **e, struct uci_list *list, const char *name)`

__Purpose__: lookup a child element

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `e` | target element pointer |
| `list` | list of elements |
| `name` | name of the child element | 

##### Notes

- if parent is NULL, the function looks up the package with the given name

### `void uci_parse_section(struct uci_section *s, const struct uci_parse_option *opts, int n_opts, struct uci_option **tb)`

__Purpose__: look up a set of options

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `ctx` | the uci context |
| `opts` | list of options to look up |
| `n_opts` | number of options to look up |
| `tb` | array of pointers to found options |

### `uint32_t uci_hash_options(struct uci_option **tb, int n_opts)`

__Purpose__: build a hash over a list of options

#### Arguments

| Argument | Description |
| -------- | ----------- |
| `tb` | list of option pointers |
| `n_opts` | number of options |

#### This was built on top of http://technostuff.blogspot.com/2017/03/openwrt-modules-uci.html

