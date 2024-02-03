return {
    {
        "williamboman/mason-lspconfig.nvim",
        dependencies = {
            "williamboman/mason.nvim",
            "neovim/nvim-lspconfig",
        },
        config = function()
            require("mason").setup()
            require("mason-lspconfig").setup({
                automatic_installation = true,
            })
            require("mason-lspconfig").setup_handlers({
                -- The first entry (without a key) will be the default handler
                -- and will be called for each installed server that doesn't have
                -- a dedicated handler.
                function (server_name) -- default handler (optional)
                    -- Set up lspconfig.
                    local capabilities = require('cmp_nvim_lsp').default_capabilities()
                    -- Replace <YOUR_LSP_SERVER> with each lsp server you've enabled.
                    require("lspconfig")[server_name].setup {
                        capabilities = capabilities
                    }
                end,
            })
        end,
    }
}
