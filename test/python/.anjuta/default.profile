<?xml version="1.0"?>
<anjuta>
    <plugin name="Terminal" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-terminal:TerminalPlugin"/>
    </plugin>
    <plugin name="Tools" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-tools:ATPPlugin"/>
    </plugin>
    <plugin name="Debugger" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-debug-manager:DebugManagerPlugin"/>
    </plugin>
    <plugin name="API Help" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-devhelp:AnjutaDevhelp"/>
    </plugin>
</anjuta>
