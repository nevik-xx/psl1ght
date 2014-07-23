.align 2
.section ".lib.ent","a"

.align 2
.section ".lib.stub","a"

.align 2
.section ".sys_proc_prx_param","a"
	.long 0x28			# Size
	.long 0x1b434cec	# Magic
	.long 2				# Version
	.long 0         	# Padding
	.long __libentstart
	.long __libentend
	.long __libstubstart
	.long __libstubend
	.short 0x0101		# Version
	.short 0			# Padding
	.long 0				# Padding
    

