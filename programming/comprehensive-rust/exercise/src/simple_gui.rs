// Design a classical GUI library.
// - Window: has a title and contains other widgets.
// - Button: has a label. In reality, it would also take a callback function
//     to allow the program to do something when the button is clicked but we
//     won’t include that since we’re only drawing the GUI.
// - Label: has a label.

// TODO: remove this when you're done with your implementation.
#![allow(unused_imports, unused_variables, dead_code)]

pub trait Widget {
    /// Natural width of `self`.
    fn width(&self) -> usize;

    /// Draw the widget into a buffer.
    fn draw_into(&self, buffer: &mut dyn std::fmt::Write);

    /// Draw the widget on standard output.
    fn draw(&self) {
        let mut buffer = String::new();
        self.draw_into(&mut buffer);
        println!("{buffer}");
    }
}

pub struct Label {
    label: String,
}

impl Label {
    fn new(label: &str) -> Label {
        Label {
            label: label.to_owned(),
        }
    }
}

pub struct Button {
    label: Label,
}

impl Button {
    fn new(label: &str) -> Button {
        Button {
            label: Label::new(label),
        }
    }
}

pub struct Column {
    ncols: usize,
    widgets: Vec<Box<dyn Widget>>,
}

pub struct Window {
    title: String,
    widgets: Vec<Box<dyn Widget>>,
}

impl Window {
    fn new(title: &str) -> Window {
        Window {
            title: title.to_owned(),
            widgets: Vec::new(),
        }
    }

    fn add_widget(&mut self, widget: Box<dyn Widget>) {
        self.widgets.push(widget);
    }

    fn inner_width(&self) -> usize {
        std::cmp::max(
            self.title.chars().count(),
            self.widgets.iter().map(|w| w.width()).max().unwrap_or(0),
        )
    }
}

impl Widget for Label {
    fn width(&self) -> usize {
        self.label.len()
    }

    fn draw_into(&self, buffer: &mut dyn std::fmt::Write) {
        let width = &self.width();
        buffer
            .write_str(format!("{}\n", self.label).as_str())
            .unwrap();
    }
}

impl Widget for Button {
    fn width(&self) -> usize {
        let padding = 4;
        self.label.width() + padding
    }

    fn draw_into(&self, buffer: &mut dyn std::fmt::Write) {
        let inner_width = self.label.width();
        let mut inner = String::new();

        self.label.draw_into(&mut inner);

        buffer
            .write_str(format!("+-{:-^inner_width$}-+\n", "").as_str())
            .unwrap();
        for line in inner.lines() {
            buffer
                .write_str(format!("| {: ^inner_width$} |\n", line).as_str())
                .unwrap();
        }
        buffer
            .write_str(format!("+-{:-^inner_width$}-+\n", "").as_str())
            .unwrap();
    }
}

impl Widget for Window {
    fn width(&self) -> usize {
        let padding = 4;
        self.inner_width() + padding
    }

    fn draw_into(&self, buffer: &mut dyn std::fmt::Write) {
        let mut inner = String::new();
        let inner_width = self.inner_width();
        for widget in &self.widgets {
            widget.draw_into(&mut inner);
        }
        // draw title
        buffer
            .write_str(format!("+-{:-^inner_width$}-+\n", "").as_str())
            .unwrap();
        for line in self.title.lines() {
            buffer
                .write_str(format!("| {:^inner_width$} |\n", line).as_str())
                .unwrap();
        }
        buffer
            .write_str(format!("+={:=^inner_width$}=+\n", "").as_str())
            .unwrap();
        // draw widgets
        for line in inner.lines() {
            buffer
                .write_str(format!("| {: <inner_width$} |\n", line).as_str())
                .unwrap();
        }
        buffer
            .write_str(format!("+-{:-^inner_width$}-+\n", "").as_str())
            .unwrap();
    }
}

pub fn simple_gui() {
    let mut window = Window::new("Rust GUI Demo 1.23");
    window.add_widget(Box::new(Label::new("This is a small text GUI demo.")));
    window.add_widget(Box::new(Button::new("Click me!")));
    window.draw();
}
