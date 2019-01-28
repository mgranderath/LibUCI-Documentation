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


### This was built on top of http://technostuff.blogspot.com/2017/03/openwrt-modules-uci.html

