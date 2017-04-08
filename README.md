# QtCpuInfo

A small Qt application (QtQuick, QML and c++) which:
- reads the std output of "cat /proc/cpuinfo" (Linux) or "sysctl -a | grep machdep.cpu" (Mac OS),
- process the std output data into custom data container for the data model,
- display the data model as TreeView UI (based on ListView),
- and optionally, automatic refresh the CPU MHz information (supported only in Linux)

Example of "cat /proc/cpuinfo" with 4 CPU cores:
processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 62
model name	: Intel(R) Xeon(R) CPU E5-1650 v2 @ 3.50GHz
stepping	: 4
microcode	: 0x416
cpu MHz		: 1217.617
cache size	: 12288 KB
physical id	: 0
siblings	: 12
core id		: 0
cpu cores	: 6
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm epb tpr_shadow vnmi flexpriority ept vpid fsgsbase smep erms xsaveopt dtherm ida arat pln pts
bugs		:
bogomips	: 6982.97
clflush size	: 64
cache_alignment	: 64
address sizes	: 46 bits physical, 48 bits virtual
power management:

processor	: 1
vendor_id	: GenuineIntel
cpu family	: 6
model		: 62
model name	: Intel(R) Xeon(R) CPU E5-1650 v2 @ 3.50GHz
stepping	: 4
microcode	: 0x416
cpu MHz		: 1240.039
cache size	: 12288 KB
physical id	: 0
siblings	: 12
core id		: 1
cpu cores	: 6
apicid		: 2
initial apicid	: 2
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm epb tpr_shadow vnmi flexpriority ept vpid fsgsbase smep erms xsaveopt dtherm ida arat pln pts
bugs		:
bogomips	: 6982.97
clflush size	: 64
cache_alignment	: 64
address sizes	: 46 bits physical, 48 bits virtual
power management:

processor	: 2
vendor_id	: GenuineIntel
cpu family	: 6
model		: 62
model name	: Intel(R) Xeon(R) CPU E5-1650 v2 @ 3.50GHz
stepping	: 4
microcode	: 0x416
cpu MHz		: 1209.277
cache size	: 12288 KB
physical id	: 0
siblings	: 12
core id		: 2
cpu cores	: 6
apicid		: 4
initial apicid	: 4
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm epb tpr_shadow vnmi flexpriority ept vpid fsgsbase smep erms xsaveopt dtherm ida arat pln pts
bugs		:
bogomips	: 6982.97
clflush size	: 64
cache_alignment	: 64
address sizes	: 46 bits physical, 48 bits virtual
power management:

processor	: 3
vendor_id	: GenuineIntel
cpu family	: 6
model		: 62
model name	: Intel(R) Xeon(R) CPU E5-1650 v2 @ 3.50GHz
stepping	: 4
microcode	: 0x416
cpu MHz		: 1218.847
cache size	: 12288 KB
physical id	: 0
siblings	: 12
core id		: 3
cpu cores	: 6
apicid		: 6
initial apicid	: 6
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm epb tpr_shadow vnmi flexpriority ept vpid fsgsbase smep erms xsaveopt dtherm ida arat pln pts
bugs		:
bogomips	: 6982.97
clflush size	: 64
cache_alignment	: 64
address sizes	: 46 bits physical, 48 bits virtual
power management:

Example of "sysctl -a | grep machdep.cpu" with 2 CPU cores:
machdep.cpu.max_basic: 13
machdep.cpu.max_ext: 2147483656
machdep.cpu.vendor: GenuineIntel
machdep.cpu.brand_string: Intel(R) Core(TM) i7-4650U CPU @ 1.70GHz
machdep.cpu.family: 6
machdep.cpu.model: 69
machdep.cpu.extmodel: 4
machdep.cpu.extfamily: 0
machdep.cpu.stepping: 1
machdep.cpu.feature_bits: 3219913727 2147154943
machdep.cpu.leaf7_feature_bits: 12219
machdep.cpu.extfeature_bits: 739248384 33
machdep.cpu.signature: 263761
machdep.cpu.brand: 0
machdep.cpu.features: FPU VME DE PSE TSC MSR PAE MCE CX8 APIC SEP MTRR PGE MCA CMOV PAT PSE36 CLFSH DS ACPI MMX FXSR SSE SSE2 SS HTT TM PBE SSE3 PCLMULQDQ DTES64 MON DSCPL VMX SMX EST TM2 SSSE3 FMA CX16 TPR PDCM SSE4.1 SSE4.2 x2APIC MOVBE POPCNT AES PCID XSAVE OSXSAVE SEGLIM64 TSCTMR AVX1.0 RDRAND F16C
machdep.cpu.leaf7_features: SMEP ENFSTRG RDWRFSGS TSC_THREAD_OFFSET BMI1 HLE AVX2 BMI2 INVPCID RTM
machdep.cpu.extfeatures: SYSCALL XD 1GBPAGE EM64T LAHF RDTSCP TSCI
machdep.cpu.logical_per_package: 16
machdep.cpu.cores_per_package: 8
machdep.cpu.microcode_version: 23
machdep.cpu.processor_flag: 6
machdep.cpu.mwait.linesize_min: 64
machdep.cpu.mwait.linesize_max: 64
machdep.cpu.mwait.extensions: 3
machdep.cpu.mwait.sub_Cstates: 286531872
machdep.cpu.thermal.sensor: 1
machdep.cpu.thermal.dynamic_acceleration: 1
machdep.cpu.thermal.invariant_APIC_timer: 1
machdep.cpu.thermal.thresholds: 2
machdep.cpu.thermal.ACNT_MCNT: 1
machdep.cpu.thermal.core_power_limits: 1
machdep.cpu.thermal.fine_grain_clock_mod: 1
machdep.cpu.thermal.package_thermal_intr: 1
machdep.cpu.thermal.hardware_feedback: 0
machdep.cpu.thermal.energy_policy: 1
machdep.cpu.xsave.extended_state: 7 832 832 0
machdep.cpu.arch_perf.version: 3
machdep.cpu.arch_perf.number: 4
machdep.cpu.arch_perf.width: 48
machdep.cpu.arch_perf.events_number: 7
machdep.cpu.arch_perf.events: 0
machdep.cpu.arch_perf.fixed_number: 3
machdep.cpu.arch_perf.fixed_width: 48
machdep.cpu.cache.linesize: 64
machdep.cpu.cache.L2_associativity: 8
machdep.cpu.cache.size: 256
machdep.cpu.tlb.inst.large: 8
machdep.cpu.tlb.data.small: 64
machdep.cpu.tlb.data.small_level1: 64
machdep.cpu.tlb.shared: 1024
machdep.cpu.address_bits.physical: 39
machdep.cpu.address_bits.virtual: 48
machdep.cpu.core_count: 2
machdep.cpu.thread_count: 4

All of above data will be proceed and displayed as tree view. Each CPU core will be represented as parent tree entry.
