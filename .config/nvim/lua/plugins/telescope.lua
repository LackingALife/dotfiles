return {
    {
        "nvim-telescope/telescope.nvim",
        dependencies = {"nvim-lua/plenary.nvim"},
        keys = {
            {'<leader>ff', "<cmd>Telescope find_files<cr>", desc = "open explorer"},
            {'<leader>fg', "<cmd>Telescope live_grep<cr>", desc = "find within files"},
            {'<leader>fb', "<cmd>Telescope buffers<cr>", desc = "file history"},
            {'<leader>fh', "<cmd>Telescope help_tags<cr>", desc = "help"},
        }
    }
}
