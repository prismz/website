#define TITLE_HEADER "<h3>"
#define SECTION_HEADER "<h4>"

static const char* html_header = 
            "<head>\n"
            "<meta charset=\"UTF-8\">\n"
            "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
            "<title>%s</title>\n"
            "<link rel=\"stylesheet\" href=\"%s\">\n"
            "</head>\n";

static const char* html_boiler_head =  
            "<!DOCTYPE html>\n"
            "<html lang=\"en\">\n"
            "%s\n"
            "</html>\n";

static const char* html_boiler_body = 
            "<body>\n"
            "%s\n"
            "</body>\n";

/*
 * this is the beginning of the content
 * list placed at the beginning of each article.
 * a closing </ul> tag will be added, so do not
 * worry about adding it here.
 */
static const char* content_list_header =
            "<br><ul class=\"section-list\">\n"
            "<li class=\"secl-header\"><h4>content</h4>\n"
            "</li>\n";
