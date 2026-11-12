; Keil C51 startup entry for the AT89S52.
; The C51 runtime performs C variable initialization after ?C_START.
$NOMOD51
NAME STARTUP
?C_STARTUP SEGMENT CODE
RSEG ?C_STARTUP
?C_STARTUP:
    LJMP ?C_START
END
