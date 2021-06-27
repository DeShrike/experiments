from fpdf import FPDF

title = "The Title"

class myPDF(FPDF):
    def header(self):
        # logo
        self.image("cat.jpeg", 10, 8, 25)
        self.set_font("helvetica", "B", 20)
        # Padding
        title_w = self.get_string_width(title) + 6
        doc_w = self.w
        self.set_x((doc_w - title_w) / 2)
        self.set_draw_color(0, 80, 100)
        self.set_fill_color(230, 230, 0)
        self.set_text_color(220, 50, 50)
        self.set_line_width(1)  # 1 mm
        self.cell(title_w, 10, title, border = True, ln = True, align = 'C', fill = True)         # Line break
        self.ln(20)

    def footer(self):
        self.set_y(-15)
        self.set_font("helvetica", "I", 10)
        self.set_text_color(189, 169, 169)
        self.cell(0, 8, f"Page {self.page_no()}/{{nb}}", align = "C")

    def chapter_title(self, title, link):
        self.set_link(link)
        self.set_font("helvetica", "", 20)
        self.set_fill_color(200, 220, 255)
        self.cell(0, 15, title, ln = True, fill = True)
        self.ln()

    def chapter_body(self, name):
        with open(name, "rb") as fh:
            txt = fh.read().decode('utf-8')
        self.set_font("times", "", 18)
        self.multi_cell(0, 8, txt, ln = True)
        self.ln(20)

    def print_chapter(self, title, chapter, link):
        self.add_page()
        self.chapter_title(title, link)
        self.chapter_body(chapter)

# Layout ('P', 'L')
# Unit ('mm', 'cm', 'in')
# Format ('A3', 'A4 (default)', 'A5', 'Letter', 'Legal', (100,150))

pdf = myPDF('P', 'mm', 'A4')

pdf.set_title(title)
pdf.set_author("I'm the author")

link1 = pdf.add_link()
link2 = pdf.add_link()
link3 = pdf.add_link()

pdf.alias_nb_pages()

pdf.set_auto_page_break(auto = True, margin = 15)

pdf.add_page()

# Fonts ('times', 'courier', 'helvetica', 'symbol', 'zpfdingbats')
# 'B' Bold, 'U' Underline, 'I' Italic, '' Regular, 'BU' combination)
pdf.set_font("helvetica", "", 16)

# Add Text

# (width, height, text)
pdf.cell(40, 20, "Hello Everybody", ln = True, border = True)

pdf.cell(80, 20, "This is cell 2", ln = True, border = True)

for i in range(41):
    pdf.cell(0, 10, f"This is line {i}", ln = True, border = True)

pdf.ln(20)

pdf.add_page()

pdf.image("cat.jpeg", x = -0.5, w = pdf.w + 1)

pdf.cell(0, 10, "A website", ln = True, link = "https://www.home.com")
pdf.cell(0, 10, "Van Halen", ln = True, link = link1)
pdf.cell(0, 10, "Jupiter", ln = True, link = link2)
pdf.cell(0, 10, "Callisto", ln = True, link = link3)

pdf.print_chapter("Van Halen", "vh.txt", link1)
pdf.print_chapter("Jupiter", "jupiter.txt", link2)
pdf.print_chapter("Callisto", "callisto.txt", link3)

pdf.output("out.pdf")


