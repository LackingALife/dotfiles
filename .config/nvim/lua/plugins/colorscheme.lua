return {

	"tanvirtin/monokai.nvim",
	name = "monokai",
	integrations = {
		mason = "true",
	},
	config = function()
		require('monokai').setup()
	end

}
