GII
======
Configuration Driven Process Wrapper.

## Build
* Qt 5.x

## process.json
Put `process.json` in your current directory, the executable file will try to load this configuration file from current directory.
* paths and command strings support using environment variables, such as `$(env.ENV_VAR)`
```
{
    "Display Name" : "the title you want to display",
    "Actions": [
        {
            "Action": "Powershell Command",
            "Type": "Command",
            "Command": "PowerShell -Command \"& {Get-AppvStatus}\""
        },
        {
            "Action": "Cmd Command",
            "Type": "Command",
            "Command": "cmd.exe /c \"ipconfig\""
        },
        {
            "Action": "Copy Folder/File",
            "Type": "Copy",
            "Source": "E:\\source_folder",
            "Destination": "E:\\dest_folder"
        },
        {
            "Action": "Delete Folder/File",
            "Type": "Delete",
            "Path": "E:\\path_to_be_delete"
        }
    ],
    "Silent": "No"
}
```