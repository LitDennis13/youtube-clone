import { create } from "zustand";


type UserLoggedIn = {
    value: {
        data: boolean;
        setUserLoggedIn: (loggedIn: boolean) => void;
    }
};

export const UserLoggedInStore = create<UserLoggedIn>((set) => ({
    value: {
        data: true,
        setUserLoggedIn: (loggedIn: boolean) => {
            set((state) => {
                state.value.data = loggedIn;
                return {value: {...state.value}};
            });
        },
    }
}));


type DisplayExtendedMenu = {
    value: {
        data: boolean,
        setDisplayExtendedMenu: (displayExtendedMenu: boolean) => void,
    }
}

export const DisplayExtendedMenuStore = create<DisplayExtendedMenu>((set) => ({
    value : {
        data: false,
        setDisplayExtendedMenu: (displayExtendedMenu: boolean) => {
            set((state) => {
                state.value.data = displayExtendedMenu;
                return {value: {...state.value}};
            });
        }
    }
}));