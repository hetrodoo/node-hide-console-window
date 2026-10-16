{
    "targets": [
        {
            "target_name": "node-hide-console-window",
            "sources": [ "node-hide-console-window.cc" ],
            "conditions": [
                ["OS=='linux'", {
                    "libraries": [ "-lX11" ]
                }]
            ]
        }
    ]
}
