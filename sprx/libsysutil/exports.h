EXPORT(videoGetResolution, 0xe558748d);
EXPORT(videoConfigure, 0x0bae8772);
EXPORT(videoGetState, 0x887572d5);

EXPORT(videoGetDeviceInfo, 0x1e930eef);
EXPORT(videoGetConfiguration, 0x15b0b0cd);
EXPORT(videoGetResolutionAvailability, 0xa322db75);
EXPORT(videoDebugSetMonitorType, 0xcfdf24bb);
EXPORT(videoRegisterCallback, 0x8e8bc444);
EXPORT(videoUnregisterCallback, 0x7871bed4);
EXPORT(videoGetNumberOfDevice, 0x75bbb672);
EXPORT(videoGetConvertCursorColorInfo, 0x55e425c3);

EXPORT(sysRegisterCallback_ex, 0x9d98afa0);
EXPORT(sysCheckCallback, 0x189a74da);
EXPORT(sysUnregisterCallback, 0x02ff3c1b);

EXPORT(msgDialogClose, 0x62b0f803);
EXPORT(msgDialogDelayedClose, 0x20543730);
EXPORT(msgDialogErrorCode_ex, 0x3e22cb4b);;
EXPORT(msgDialogOpen_ex, 0xf81eca25);
EXPORT(msgDialogIncProgressBar, 0x94862702);
EXPORT(msgDialogAbort, 0x62b0f803);
EXPORT(msgDialogOpen2_ex, 0x7603d3db);
EXPORT(msgDialogResetProgressBar, 0x7bc2c8a8);
EXPORT(msgDialogProgressBarMessage, 0x9d6af72a);

EXPORT(oskGetInputText, 0x1d99c3ee);
EXPORT(oskSetInitialInputDevice, 0xf3b4b43e);
EXPORT(oskGetSize, 0x35beade0);
EXPORT(oskUnloadAsync, 0x3d1e1931);
EXPORT(oskDisableDimmer, 0x41f20828);
EXPORT(oskSetKeyLayoutOption, 0xb53c54fa);
EXPORT(oskAbort, 0xb6d84526);
EXPORT(oskSetDeviceMask, 0xd3790a86);
EXPORT(oskSetSeparateWindowOption, 0x53e39df3);
EXPORT(oskAddSupportLanguage, 0x7f21c918);
EXPORT(oskLoadAsync, 0x7fcfc915);
EXPORT(oskSetInitialKeyLayout, 0xc427890c);
EXPORT(oskSetLayoutMode, 0xf0ec3ccc);

/* Disc utility support */
EXPORT(sysDiscRegisterDiscChangeCallbackEx, 0xdfdd302e);
EXPORT(sysDiscUnregisterDiscChangeCallback, 0xedc34e1a);