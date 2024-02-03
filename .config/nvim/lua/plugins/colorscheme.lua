return {

	"navarasu/onedark.nvim",
	name = "onedark",
	integrations = {
		mason = "true",
	},
	config = function()
		require('onedark').setup {
			style = 'darker'
		}
		require('onedark').load()
	end

}
