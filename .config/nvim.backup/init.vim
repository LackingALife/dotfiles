
set tabstop=4
set shiftwidth=4
set number

call plug#begin('~/.vim/plugged')

Plug 'ful1e5/onedark.nvim'
Plug 'nvim-treesitter/nvim-treesitter', {'do': ':TSUpdate'}
Plug 'nvim-neo-tree/neo-tree.nvim'
Plug 'nvim-lua/plenary.nvim'
Plug 'nvim-tree/nvim-web-devicons'
Plug 'MunifTanjim/nui.nvim'
Plug 'neovim/nvim-lspconfig'
Plug 'VonHeikemen/lsp-zero.nvim'
Plug 'williamboman/mason.nvim'
Plug 'williamboman/mason-lspconfig.nvim'
Plug 'hrsh7th/cmp-nvim-lsp'
Plug 'hrsh7th/cmp-buffer'
Plug 'hrsh7th/cmp-path'
Plug 'hrsh7th/cmp-cmdline'
Plug 'hrsh7th/nvim-cmp'
Plug 'akinsho/toggleterm.nvim', {'tag' : '*'}
Plug 'L3MON4D3/LuaSnip'
Plug 'chrisgrieser/nvim-tinygit'
Plug 'nyoom-engineering/oxocarbon.nvim'
Plug 'bluz71/vim-nightfly-colors', { 'as': 'nightfly' }

call plug#end()

lua require('config')

let g:onedark_config = {
  \ 'style': 'dark',
  \ 'toggle_style_key': '<leader>ts',
  \ 'ending_tildes': v:true,
  \ 'diagnostics': {
    \ 'darker': v:true,
    \ 'background': v:true,
  \ },
\ }
colorscheme nightfly
