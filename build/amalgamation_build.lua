function amalgamation_build()

    local content = darwin.mdeclare.transform_dir({
        dir="src",
        startswith="fdefine",
        endswith=".c",
    })

    darwin.dtw.write_file("src/fdeclare.all.h", content)
    darwin.silverchain.remove("src/fdeclare.all.h")


   darwin.silverchain.generate({
        src = "src",
        tags = { "dep_declare","consts", "macros", "types", "fdeclare","globals", "dep_define","fdefine" },
        project_short_cut = "doTheWorld",
        implement_main = false
    })

    local MAX_CONNTENT = darwin.camalgamator.ONE_MB * 20
    local MAX_RECURSION = 100

    local lincense = "/* " .. darwin.dtw.load_file("LICENSE") .. " */ \n"

    local onefile = darwin.camalgamator.generate_amalgamation("src/one.c", MAX_CONNTENT, MAX_RECURSION)
    onefile = lincense .. onefile

    darwin.dtw.write_file("release/doTheWorldOne.c", onefile)

    local only_declare = darwin.camalgamator.generate_amalgamation("src/imports/imports.fdeclare.h", MAX_CONNTENT,
    MAX_RECURSION)
    only_declare = lincense .. only_declare
    darwin.dtw.write_file("release/doTheWorld.h", only_declare)



    local only_definition = darwin.camalgamator.generate_amalgamation_with_callback("src/imports/imports.fdefine.h",
        function(import, path)
            if darwin.dtw.ends_with(import, ".c") then
                return "include-once"
            end
            return "dont-include"
        end,
        MAX_CONNTENT,
        MAX_RECURSION
    )

    



end

darwin.add_recipe({
    name="amalgamation_build",
    description="make a amalgamation files and a zip",
    outs={"release/doTheWorld.h", "release/doTheWorldOne.c", "release/doTheWorld.zip"},
    inputs={"src","dependencies","build"},
    callback=amalgamation_build
})