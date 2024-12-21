function Install_dependencies()
    os.execute(
        "curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.c -o dependencies/cJSON.c")
    os.execute(
        "curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.h -o dependencies/cJSON.h")

    os.execute(
        "curl -L https://raw.githubusercontent.com/amosnier/sha-2/565f65009bdd98267361b17d50cddd7c9beb3e6c/sha-256.c -o dependencies/sha-256.c  "
    )
    os.execute(
        "curl -L https://raw.githubusercontent.com/amosnier/sha-2/565f65009bdd98267361b17d50cddd7c9beb3e6c/sha-256.h -o dependencies/sha-256.h  "
    )

    os.execute(
        "curl -L https://github.com/OUIsolutions/CHashManipulator/releases/download/0.001/CHashManipulator.h -o dependencies/CHashManipulator.h "
    )
end
