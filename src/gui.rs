use eframe::egui;

struct MyApp {
    name: String,
    age: i32,
}

impl Default for MyApp {
    fn default() -> Self {
        Self { name: String::from("Magda"), age: 23 }
    }
}

impl eframe::App for MyApp {
    fn update(&mut self, ctx: &eframe::egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Hello World");
            ui.horizontal(|ui| {
                let name_label = ui.label("Your name: ");
                ui.text_edit_singleline(&mut self.name).labelled_by(name_label.id);
            });
            ui.add(egui::Slider::new(&mut self.age, 0..=120).text("age"));
            if ui.button("Increment").clicked() {
                self.age += 1;
            }
            ui.label(format!("Hello '{}', age '{}'", self.name, self.age));
        });
    }
}

#[allow(dead_code)]
pub(crate) fn run_ui() {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default().with_inner_size([320.0, 240.0]),
        ..Default::default()
    };
    let _ = eframe::run_native("My Egui App", options, Box::new(|_cc| {
        Ok(Box::<MyApp>::default())
    }));
}
