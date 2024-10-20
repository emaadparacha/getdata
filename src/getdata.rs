// getdata Bindings
use getdata_bindings::*;
use std::ffi::{CString, CStr};
use std::any::Any;

pub struct DirFile {
    pub dirfile_open: *mut DIRFILE,
}

impl DirFile {

    // Function to create a new DirFile instance from a path
    pub fn new(path: &str) -> Self {
        let dirfile = CString::new(path).expect("CString::new failed");
        let dirfile_ptr = dirfile.as_ptr();
        let dirfile_open = unsafe { gd_open(dirfile_ptr, GD_RDONLY) };
        Self {
            dirfile_open,
        }
    }

    // Function to get the number of fields in the DirFile
    pub fn nfields(&self) -> usize {
        unsafe { gd_nfields(self.dirfile_open) }
    }

    // Function to get the total number of frames in a DirFile
    pub fn nframes(&self) -> usize {
        unsafe { gd_nframes(self.dirfile_open) }
    }

    // Function to get the samples per frame for a field in a DirFile
    pub fn spf(&self, field: &str) -> usize {
        let field_code = CString::new(field).expect("CString::new failed");
        let field_code_ptr = field_code.as_ptr();
        unsafe { gd_spf(self.dirfile_open, field_code_ptr) }
    }

    // Function to get the type of a field in a DirFile
    pub fn field_type(&self, field: &str) -> i32 {
        let field_code = CString::new(field).expect("CString::new failed");
        let field_code_ptr = field_code.as_ptr();
        unsafe { gd_native_type(self.dirfile_open, field_code_ptr) }
    }

    // Function to get the data of a field in a DirFile
    pub fn get_data(&self, field: &str) -> Vec<Box<dyn Any>> {
        let field_type = self.field_type(field);
        let nframes = self.nframes();
        let samples_per_frame = self.spf(field);
        let total_samples = nframes * samples_per_frame;

        match field_type {
            gd_type_t_GD_UINT8 => {
                let mut data = vec![0u8; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT8,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_INT8 => {
                let mut data = vec![0i8; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT8,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_UINT16 => {
                let mut data = vec![0u16; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT16,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_INT16 => {
                let mut data = vec![0i16; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT16,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_UINT32 => {
                let mut data = vec![0u32; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT32,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_INT32 => {
                let mut data = vec![0i32; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT32,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_UINT64 => {
                let mut data = vec![0u64; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT64,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_INT64 => {
                let mut data = vec![0i64; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT64,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_FLOAT32 => {
                let mut data = vec![0.0f32; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_FLOAT32,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_FLOAT64 => {
                let mut data = vec![0.0f64; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_FLOAT64,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            gd_type_t_GD_STRING => {
                // Handle string data accordingly, may need adjustment for your specific needs
                let mut data = vec![CString::new("").unwrap(); total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        CString::new(field).unwrap().as_ptr(),
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_STRING,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                let data: Vec<String> = data.into_iter().map(|c| c.into_string().unwrap()).collect();
                data.into_iter().map(|v| Box::new(v) as Box<dyn Any>).collect()
            }
            _ => Vec::new(), // Handle unknown types
        }
    }

}