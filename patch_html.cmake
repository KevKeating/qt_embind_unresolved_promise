file(READ "${HTML_FILE}" content)
string(REPLACE
    "const instance = await qtLoad("
    "const instance = window.Module = await qtLoad("
    content "${content}"
)
file(WRITE "${HTML_FILE}" "${content}")
