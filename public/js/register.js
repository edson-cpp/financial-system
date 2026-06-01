const formatPhone = (value) => {
    const digits = value.replace(/\D/g, "").slice(0, 11);

    if (digits.length <= 2) {
        return digits ? `(${digits}` : "";
    }

    if (digits.length <= 7) {
        return `(${digits.slice(0, 2)}) ${digits.slice(2)}`;
    }

    return `(${digits.slice(0, 2)}) ${digits.slice(2, 7)}-${digits.slice(7)}`;
};

function initRegisterForm() {
    const form = document.querySelector(".sysform-form");
    const phoneInput = document.querySelector("#phone");
    const validatedInputs = document.querySelectorAll("#email, #phone");

    if (!form || !phoneInput) {
        return;
    }

    const refreshValidationState = (input) => {
        const shouldValidate = input.dataset.touched === "true" || form.dataset.submitted === "true";
        const isInvalid = shouldValidate && input.value.trim() !== "" && !input.validity.valid;
        input.classList.toggle("is-invalid", isInvalid);
        input.closest(".form-line").classList.toggle("form-line-error", isInvalid);
    };

    phoneInput.value = formatPhone(phoneInput.value);

    phoneInput.addEventListener("input", () => {
        phoneInput.value = formatPhone(phoneInput.value);
        refreshValidationState(phoneInput);
    });

    validatedInputs.forEach((input) => {
        input.addEventListener("blur", () => {
            input.dataset.touched = "true";
            refreshValidationState(input);
        });

        input.addEventListener("input", () => refreshValidationState(input));
    });

    form.addEventListener("submit", (event) => {
        form.dataset.submitted = "true";
        validatedInputs.forEach(refreshValidationState);

        if (!form.checkValidity()) {
            event.preventDefault();
            form.reportValidity();
        }
    });
}

window.initRegisterForm = initRegisterForm;

document.addEventListener("DOMContentLoaded", initRegisterForm);
