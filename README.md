# LibUCI-Documentation
Documentation for the libuci c interface

## `struct uci_context *uci_alloc_context(void)`

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

#### This was built on top of http://technostuff.blogspot.com/2017/03/openwrt-modules-uci.html

