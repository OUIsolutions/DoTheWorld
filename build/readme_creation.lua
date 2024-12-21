---@return string |nil
function Create_readme()
    local result = candango.Render_text(
        dtw.load_file("INTERNAL.md")
    )
    dtw.write_file("README.md", result.render_text)
end
