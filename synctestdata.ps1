# Script that synchronizes the local test data
#
# Version: 20260531

$Repository = "dfirlabs/cue-specimens"
$TestDataPath = "specimens/cdrdao"
$TestSet = "public"
$TestInputDirectory = "tests\input"
$TestFiles = "image.bin image.cue"

If (-Not (Test-Path ${TestInputDirectory}))
{
	New-Item -Name ${TestInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
	New-Item -Name "${TestInputDirectory}\.libodraw\${TestSet}" -ItemType "directory" | Out-Null
	New-Item -Name "${TestInputDirectory}\.odrawinfo\${TestSet}" -ItemType "directory" | Out-Null
	New-Item -Name "${TestInputDirectory}\.odrawverify\${TestSet}" -ItemType "directory" | Out-Null
}
ForEach ($TestFile in ${TestFiles} -split " ")
{
	$Url = "https://raw.githubusercontent.com/${Repository}/refs/heads/main/${TestDataPath}/${TestFile}"

	Invoke-WebRequest -Uri ${Url} -OutFile "${TestInputDirectory}\${TestSet}\${TestFile}"
}

"image.cue" | Out-File -Encoding ascii "${TestInputDirectory}\.libodraw\${TestSet}\files"
"image.cue" | Out-File -Encoding ascii "${TestInputDirectory}\.odrawinfo\${TestSet}\files"
"image.cue" | Out-File -Encoding ascii "${TestInputDirectory}\.odrawverify\${TestSet}\files"

$Content = Get-Content -Path "${TestInputDirectory}\${TestSet}\image.cue"
$Content -Replace "specimens/cdrdao/","" | Set-Content -Path "${TestInputDirectory}\${TestSet}\image.cue"
