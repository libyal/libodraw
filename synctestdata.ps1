# Script that synchronizes the local test data

$TestsInputDirectory = "tests\input"
$TestSet = "public"
$TestFiles = "image.bin image.cue"

If (-Not (Test-Path ${TestsInputDirectory}))
{
	New-Item -Name ${TestsInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestsInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestsInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
}
ForEach ($TestFile in ${TestFiles} -split " ")
{
	$UrlTestFile = [System.Uri]::EscapeDataString("${TestFile}")
	$Url = "https://raw.githubusercontent.com/dfirlabs/cue-specimens/refs/heads/main/specimens/cdrdao/${UrlTestFile}"

	$ProgressPreference = 'SilentlyContinue'
	Invoke-WebRequest -Uri ${Url} -OutFile "${TestsInputDirectory}\${TestSet}\${TestFile}"
}

$Content = Get-Content -Path "${TestsInputDirectory}\${TestSet}\image.cue"
$Content -Replace "specimens/cdrdao/","" | Set-Content -Path "${TestsInputDirectory}\${TestSet}\image.cue"

New-Item -Name "${TestsInputDirectory}\.libodraw\${TestSet}" -ItemType "directory" | Out-Null
"image.cue" | Out-File -Encoding ascii "${TestsInputDirectory}\.libodraw\${TestSet}\files"

New-Item -Name "${TestsInputDirectory}\.odrawinfo\${TestSet}" -ItemType "directory" | Out-Null
"image.cue" | Out-File -Encoding ascii "${TestsInputDirectory}\.odrawinfo\${TestSet}\files"

New-Item -Name "${TestsInputDirectory}\.odrawverify\${TestSet}" -ItemType "directory" | Out-Null
"image.cue" | Out-File -Encoding ascii "${TestsInputDirectory}\.odrawverify\${TestSet}\files"
