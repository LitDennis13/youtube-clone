export enum PageOptions {
    SignInSignUp,
    Home,
    Subscription,
    History,
    Playlists,
    MyVideos,
};


export type VideoType = {
    name: string;
    channelName: string;
    views: number;
    length: number;
    videoThumbnail: string;
};