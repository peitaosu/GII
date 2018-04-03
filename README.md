GII
======

[![GitHub license](https://img.shields.io/github/license/peitaosu/GII.svg)](https://github.com/peitaosu/GII/blob/master/LICENSE)

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
In Windows, it also support registry operations:
```
        {
            "Action": "Set Registry Value",
            "Type": "Registry",
            "Func": "Set",
            "Root": "HKLM",
            "Key": "Software",
            "Name": "Test",
            "Type": "SZ",
            "Value": "Test"
        },
        {
            "Action": "Delete Registry Value",
            "Type": "Registry",
            "Func": "Delete",
            "Root": "HKCU",
            "Key": "Software",
            "Name": "Test",
            "Type": "",
            "Value": ""
        },
        {
            "Action": "Unload Registry Key",
            "Type": "Registry",
            "Func": "Unload",
            "Root": "HKCR",
            "Key": "Test",
            "Name": "",
            "Type": "",
            "Value": ""
        }
```