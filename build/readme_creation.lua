function create_c_example(src)
    local content = dtw.load_file(src)

    return "```c\n" .. content .. "\n```"
end

---@return string |nil
function Create_readme()
    local result = candango.Render_text(
        dtw.load_file("extras/INTERNAL.md")
    )
    if result.exist_error then
        print(result.error_message)
        os.exit(1)
    end
    dtw.write_file("README.md", result.render_text)
end
