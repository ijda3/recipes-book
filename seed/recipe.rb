require 'rest-client'
require 'nokogiri'

def remove_accents(str)
  str.tr(
    "ÀÁÂÃÄÅàáâãäåĀāĂăĄąÇçĆćĈĉĊċČčÐðĎďĐđÈÉÊËèéêëĒēĔĕĖėĘęĚěĜĝĞğĠġĢģĤĥĦħÌÍÎÏìíîïĨĩĪīĬĭĮįİıĴĵĶķĸĹĺĻļĽľĿŀŁłÑñŃńŅņŇňŉŊŋÒÓÔÕÖØòóôõöøŌōŎŏŐőŔŕŖŗŘřŚśŜŝŞşŠšſŢţŤťŦŧÙÚÛÜùúûüŨũŪūŬŭŮůŰűŲųŴŵÝýÿŶŷŸŹźŻżŽž",
    "AAAAAAaaaaaaAaAaAaCcCcCcCcCcDdDdDdEEEEeeeeEeEeEeEeEeGgGgGgGgHhHhIIIIiiiiIiIiIiIiIiJjKkkLlLlLlLlLlNnNnNnNnnNnOOOOOOooooooOoOoOoRrRrRrSsSsSsSssTtTtTtUUUUuuuuUuUuUuUuUuUuWwYyyYyYZzZzZz")
end

def css_list(doc, selector)
  i = 0

  lists = doc.css(selector)
  items = []

  loop do
    items = lists[i].children

    break unless items.empty?

    i += 1
  end

  items.map do |element|
    element.children.children.to_s
  end&.join(', ')&.tr("\n","").gsub(/<[^>]*>/ui,'')
end

def get_recipe(url)
  response = RestClient.get(url)
  doc = Nokogiri::HTML(response.body)

  {
    title: remove_accents(doc.css('.recipe-title h1').first&.content&.tr("\n","").upcase),
    duration: doc.css('.preptime > .dt-duration').first&.content&.tr("\n","").to_i,
    rating: doc.css('.ratingstars > span:last-child').first&.content&.tr("\n",""),
    ingredient: remove_accents(css_list(doc, '#info-user > ul')),
    directions: remove_accents(css_list(doc, '.instructions.e-instructions > ol')),
    author: remove_accents(doc.css('.author-name > span').first&.content&.tr("\n","")),
  }
end

total = 1000
count = 0
ids = []
names = []

while(count < total)
  threads = []
  recipes = []
  diff = total - count

  (diff <= 50 ? diff : 50).times {
    threads << Thread.new do
      begin
        id = rand(1..307467)

        unless ids.include?(id)
		  recipe = get_recipe("https://www.tudogostoso.com.br/receita/#{id}")

		  unless names.include?(recipe[:title])
			if recipe[:title] && recipe[:duration] && recipe[:rating] && recipe[:ingredient] && recipe[:directions] && recipe[:author]
				ids << id
				names << recipe[:title]
				recipes << recipe

				puts "%s - %s" % [id, recipe[:title]]

				count += 1;
			end
		  end
        end
      rescue => e
      end
    end
  }

  threads.each(&:join)

  recipes.each do |recipe|
	command = <<~CMD
	./seed "#{recipe[:title]}" "#{recipe[:duration]}" "#{recipe[:rating]}" "#{recipe[:ingredient]}" "#{recipe[:directions]}" "#{recipe[:author]}"
CMD
	puts command
	unless system(command)
	  count -= 1
	end
  end
  print "\n --- #{count}/#{total} --- \n\n"
end

print 'fim'
